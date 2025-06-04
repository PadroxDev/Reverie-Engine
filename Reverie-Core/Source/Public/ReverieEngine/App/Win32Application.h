#pragma once

#include "stdafx.h"

struct IDXGISwapChain;

namespace ReverieEngine::App
{
    class BaseClientApp;
    
    class Win32Application
    {
    public:
        int Run(BaseClientApp* clientApp, HINSTANCE hInstance, int nCmdShow);
        void ToggleFullscreenWindow(IDXGISwapChain* pOutput = nullptr);
        void SetWindowZorderToTopMost(BOOL setToTopMost);
        HWND GetHwnd() const { return m_hwnd; }
        BOOL IsFullscreen() const { return m_bFullscreen; }

    protected:
        Win32Application();
        virtual ~Win32Application() = default;
        
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        
    private:
        HWND m_hwnd;
        BOOL m_bFullscreen;
        RECT m_windowRect;

        constexpr UINT m_WindowStyle = WS_OVERLAPPEDWINDOW;
    };

}
