#include "Core/ReverieApp.h"

ReverieEngine::Core::ReverieApp::ReverieApp(int width, int height, std::wstring title) : ReverieGraphicsHandle(width,
    height, std::move(title))
{ }

void ReverieEngine::Core::ReverieApp::OnInit()
{
    ReverieGraphicsHandle::OnInit();
}

void ReverieEngine::Core::ReverieApp::OnUpdate()
{
}

void ReverieEngine::Core::ReverieApp::OnRender()
{
}

void ReverieEngine::Core::ReverieApp::OnDestroy()
{
}