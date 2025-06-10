#include "ReverieEngine.h"

using namespace ReverieEngine::App;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    std::unique_ptr<Win32Application> win32App; 
    std::unique_ptr<ReverieApp> reverieApp = ReverieApp::CreateWithWin32(1280, 720, L"Reverie Game", &win32App);
    return win32App->Run(hInstance, nCmdShow);
}