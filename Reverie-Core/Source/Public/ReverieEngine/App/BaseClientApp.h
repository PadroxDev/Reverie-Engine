#pragma once

#include <string>

#include "stdafx.h"

namespace ReverieEngine::App
{
    class BaseClientApp
    {
    public:
        BaseClientApp(int width, int height, std::wstring title);
        virtual ~BaseClientApp() = default;

        virtual void OnInit() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;
        virtual void OnDestroy() = 0;
        
        virtual void OnDisplayChanged() { }
        virtual void OnWindowMoved(int x, int y) { }
        virtual void OnWindowSizeChanged(int width, int height, bool minimized) { }

    #pragma region Accessors
        
        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }
        const wchar_t* GetWindowTitle() const { return m_windowTitle.c_str(); }
        RECT GetWindowBounds() const { return m_windowBounds; }

    #pragma endregion

        void UpdateForSizeChange(UINT clientWidth, UINT clientHeight);
        void SetWindowBounds(const RECT& newRect);
        
    protected:
        // TODO: void SetWindowTitle(const std::wstring& title);
        
        UINT m_width;
        UINT m_height;
        float m_aspectRatio;
        RECT m_windowBounds;
    
    private:
        std::wstring m_windowTitle;
        
    };

}
