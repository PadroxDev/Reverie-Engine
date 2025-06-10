#pragma once

#include "stdafx.h"

struct IDXGISwapChain;

namespace ReverieEngine::App
{
    class BaseClientApp;
    
    class Win32Application
    {
    public:
        Win32Application();
        virtual ~Win32Application() = default;

        void BindToClientApp(BaseClientApp* clientApp);
        int Run(HINSTANCE hInstance, int nCmdShow);
        
        void ToggleFullscreenWindow(IDXGISwapChain* pOutput = nullptr);
        void SetWindowZOrderToTopMost(BOOL setToTopMost);

        BaseClientApp* GetClientApp() const { return m_clientApp; }
        HWND GetHwnd() const { return m_hwnd; }
        BOOL IsFullscreen() const { return m_bFullscreen; }

    protected:
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        
    private:
        HWND m_hwnd;
        BOOL m_bFullscreen;
        RECT m_windowRect;

        BaseClientApp* m_clientApp;
        
        const UINT m_WindowStyle = WS_OVERLAPPEDWINDOW;
    };

}
