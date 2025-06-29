#pragma once

#include "ReverieEngine/Core/stdafx.h"
#include "ReverieEngine/Core/App/Enums/FullscreenMode.h"

struct IDXGISwapChain;

namespace ReverieEngine::Core::App
{
    class BaseClientApp;
    
    class Win32Application
    {
    public:
        Win32Application();
        virtual ~Win32Application() = default;

        void BindToClientApp(BaseClientApp* pClientApp);
        int Run(HINSTANCE hInstance, int nCmdShow);

        void SetFullscreenMode(FullscreenMode mode);
        void ToggleFullscreenMode();
        void SetWindowZOrderToTopMost(BOOL setToTopMost);

        BaseClientApp* GetClientApp() const { return m_clientApp; }
        HWND GetHwnd() const { return m_hwnd; }
        FullscreenMode GetFullscreenMode() const { return m_currentFullscreenMode; }
        bool IsWindowed() const { return m_currentFullscreenMode == FullscreenMode::Windowed; }
        bool IsBorderlessFullscreen() const { return m_currentFullscreenMode == FullscreenMode::Borderless; }

    protected:
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        
    private:
        HWND m_hwnd;
        RECT m_windowRect;
        FullscreenMode m_currentFullscreenMode;
        const UINT m_kWindowStyle = WS_OVERLAPPEDWINDOW;
        
        BaseClientApp* m_clientApp;
    };

}
