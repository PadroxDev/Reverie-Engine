#pragma once

#include "pch.h"
#include "Core/App/Enums/FullscreenMode.h"

struct IDXGISwapChain;

namespace ReverieEngine
{
    namespace Core
    {
        class BaseClientApp;
    }
    
    class Win32Application
    {
    public:
        Win32Application();
        virtual ~Win32Application() = default;

        void BindToClientApp(Core::BaseClientApp* pClientApp);
        int Run(HINSTANCE hInstance, int nCmdShow);

        void SetFullscreenMode(EFullscreenMode mode);
        void ToggleFullscreenMode();
        void SetWindowZOrderToTopMost(BOOL setToTopMost);

        Core::BaseClientApp* GetClientApp() const { return m_clientApp; }
        HWND GetHwnd() const { return m_hwnd; }
        EFullscreenMode GetFullscreenMode() const { return m_currentFullscreenMode; }
        bool IsWindowed() const { return m_currentFullscreenMode == EFullscreenMode::Windowed; }
        bool IsBorderlessFullscreen() const { return m_currentFullscreenMode == EFullscreenMode::Borderless; }

    protected:
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        
    private:
        HWND m_hwnd;
        RECT m_windowRect;
        EFullscreenMode m_currentFullscreenMode;
        const UINT m_kWindowStyle = WS_OVERLAPPEDWINDOW;
        
        Core::BaseClientApp* m_clientApp;
    };

}
