#include "Core/ReverieApp.h"

#include "App/Win32Application.h"

using namespace ReverieEngine::Core;

std::unique_ptr<ReverieApp> ReverieApp::CreateWithWin32(UINT width, UINT height, const std::wstring& title,
    std::unique_ptr<App::Win32Application>* outWin32App)
{
    auto app = std::make_unique<ReverieApp>(width, height, std::move(title));
    auto win32 = std::make_unique<App::Win32Application>();

    app->BindToWin32App(win32.get());
    win32->BindToClientApp(app.get());
        
    if(outWin32App)
        *outWin32App = std::move(win32);
        
    return app;
}

void ReverieApp::OnInit()
{ }

void ReverieApp::OnUpdate()
{ }

void ReverieApp::OnRender()
{ }

void ReverieApp::OnDestroy()
{ }