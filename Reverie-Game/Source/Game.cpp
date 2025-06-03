#include "ReverieEngine.h"

using namespace ReverieEngine::Core;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    ReverieApp graphicsHandle = ReverieApp(1280, 720);
    return graphicsHandle.Run(hInstance, nCmdShow);
}