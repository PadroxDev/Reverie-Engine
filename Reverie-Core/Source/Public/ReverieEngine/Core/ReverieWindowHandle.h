#pragma once

#include <wrl/client.h>
#include <string>

using Microsoft::WRL::ComPtr;

struct IDXGISwapChain;

namespace ReverieEngine::Core
{
    class ReverieWindowHandle
    {
    public:
        ReverieWindowHandle(int width = 1280, int height = 720, const std::wstring& title = L"Reverie Window");
        virtual ~ReverieWindowHandle();
        ReverieWindowHandle(const ReverieWindowHandle&) = default;
        ReverieWindowHandle& operator=(const ReverieWindowHandle&) = delete;
        ReverieWindowHandle(ReverieWindowHandle&&) = default;
        ReverieWindowHandle& operator=(ReverieWindowHandle&&) = delete;

        virtual int Run(HINSTANCE hInstance, int nCmdShow);

        void ToggleFullsreenWindow(IDXGISwapChain* pOutput = nullptr);
        void SetWindowZorderToTopMost(bool bSetToTopMost);
        HWND GetHwnd() const { return m_hwnd; }
        bool IsFullscreen() const { return m_bFullscreen; }

    protected:
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        // Callback methods to hook into the window lifecycle.
        virtual void OnInit() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;
        virtual void OnWindowSizeChanged(int width, int height, bool minimized);
        virtual void OnWindowMoved(int x, int y);
        virtual void OnDisplayChanged();
        virtual void OnDestroy() = 0;
        
    private:
        void SetWindowBounds(const RECT& windowRect);
        
        UINT m_width;
        UINT m_height;
        FLOAT m_aspectRatio;
        std::wstring m_title;
        
        HWND m_hwnd;
        BOOL m_bFullscreen;
        RECT m_windowRect;
        RECT m_windowBounds;
        
        const UINT m_WindowStyle = WS_OVERLAPPEDWINDOW;
    };

}
