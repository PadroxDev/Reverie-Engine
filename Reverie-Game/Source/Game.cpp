#include <ReverieEngine.h>

using namespace rev;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    Vector2 v1 = Vector2(1, 0);
    Vector2 v2 = Vector2(0, -1);
    
    float angle = Vector2::Angle(v1, v2);
    float signedAngle = Vector2::SignedAngle(v1, v2);
    
    OutputCtxDebug(std::to_wstring(Math::E));
    
     std::unique_ptr<Win32Application> win32App; 
     std::unique_ptr<ReverieApp> reverieApp = ReverieApp::CreateWithWin32(1280, 720, L"Reverie Game", &win32App);
     return win32App->Run(hInstance, nCmdShow);
}