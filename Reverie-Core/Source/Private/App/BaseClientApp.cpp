#include "ReverieEngine/App/BaseClientApp.h"

#include "ReverieEngine/App/Win32Application.h"
#include "ReverieEngine/Util/DebugUtil.h"

using namespace ReverieEngine::App;

void BaseClientApp::BindToWin32App(Win32Application* app)
{
    if(m_win32App != nullptr)
    {
        OutputCtxDebug(L"BaseClientApp is already bound to a Win32Application instance!");
        return;
    }
    
    m_win32App = app;
}

BaseClientApp::BaseClientApp(UINT width, UINT height, std::wstring title) :
    m_aspectRatio(0.f),
    m_windowBounds({}),
    m_adapterIDoverride(UINT_MAX),
    m_windowTitle(std::move(title)),
    m_win32App(nullptr)
{
    UpdateForSizeChange(width, height);
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

void BaseClientApp::SetWindowTitle(const std::wstring& title) const
{
    SetWindowText(m_win32App->GetHwnd(), title.c_str());
}