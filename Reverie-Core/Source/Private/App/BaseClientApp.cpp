#include "App/BaseClientApp.h"

namespace ReverieEngine::App {
    BaseClientApp::BaseClientApp(int width, int height, std::wstring title) :
        m_width(width),
        m_height(height),
        m_aspectRatio(0.f),
        m_windowBounds({}),
        m_windowTitle(std::move(title))
    {
        m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
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
}
