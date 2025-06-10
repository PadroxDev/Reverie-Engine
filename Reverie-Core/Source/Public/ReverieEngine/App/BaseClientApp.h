#pragma once

#include "stdafx.h"

#include <string>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

namespace ReverieEngine::App
{
    class Win32Application;
    
    class BaseClientApp
    {
    public:
        virtual void OnInit() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;
        virtual void OnDestroy() = 0;
        
        virtual void OnDisplayChanged() { }
        virtual void OnWindowMoved(int x, int y) { }
        virtual void OnWindowSizeChanged(int width, int height, bool minimized) { }

    #pragma region Accessors
        
        UINT GetWidth() const { return m_width; }
        UINT GetHeight() const { return m_height; }
        const wchar_t* GetWindowTitle() const { return m_windowTitle.c_str(); }
        RECT GetWindowBounds() const { return m_windowBounds; }
        virtual IDXGISwapChain* GetSwapchain() const { return nullptr; }
        DX::DeviceResources* GetDeviceResources() const { return m_deviceResources.get(); }
        
    #pragma endregion

        // Bidirectional binding to Win32Application that powers this client app.
        void BindToWin32App(Win32Application* app);
        
        void UpdateForSizeChange(UINT clientWidth, UINT clientHeight);
        void SetWindowBounds(const RECT& newRect);
        
    protected:
        BaseClientApp(UINT width, UINT height, std::wstring title);
        virtual ~BaseClientApp() = default;
        
        void SetWindowTitle(const std::wstring& title) const;

        Win32Application* m_win32App; 
        
        UINT m_width;
        UINT m_height;
        float m_aspectRatio;

        RECT m_windowBounds;

        UINT m_adapterIDoverride;
        std::unique_ptr<DX::DeviceResources> m_deviceResources;
        
    private:
        std::wstring m_windowTitle;
        
    };

}
