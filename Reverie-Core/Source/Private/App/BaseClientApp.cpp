#include "App/BaseClientApp.h"

namespace ReverieEngine::App {
    BaseClientApp::BaseClientApp(UINT width, UINT height, std::wstring title) :
        m_aspectRatio(0.f),
        m_windowBounds({}),
        m_adapterIDoverride(UINT_MAX),
        m_windowTitle(std::move(title))
    {
        UpdateForSizeChange(width, height);
    }

    void BaseClientApp::BindToWin32App(Win32Application* app)
    {
        
    }

    void BaseClientApp::UpdateForSizeChange(UINT clientWidth, UINT clientHeight)
    {
        m_width = clientWidth;
        m_height = clientHeight;
        m_aspectRatio = static_cast<float>(clientWidth) / static_cast<float>(clientHeight);
    }

    void BaseClientApp::SetWindowBounds(const RECT& newRect)
    {
        m_windowBounds = newRect;
    }

    void BaseClientApp::SetWindowTitle(const std::wstring& title)
    {
        SetWindowText()
    }
}
