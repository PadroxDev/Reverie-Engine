#include <ReverieEngine.h>

using namespace rev;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    float distance = 3;
    Vector2 v1 = Vector2(0, 2);
    Vector2 v2 = v1 + Vector2(1, 0) * distance;
    Vector2 v1Tov2 = (v1 - v2).FastNormalized();
    float mag = v1Tov2.Length();

    OutputCtxDebug(Vector2::Lerp(v1, v2, 3.0f).ToString());
    OutputCtxDebug(Vector2::LerpUnclamped(v1, v2, 3.0f).ToString());
    
    //
    // std::unique_ptr<Win32Application> win32App; 
    // std::unique_ptr<ReverieApp> reverieApp = ReverieApp::CreateWithWin32(1280, 720, L"Reverie Game", &win32App);
    // return win32App->Run(hInstance, nCmdShow);
}