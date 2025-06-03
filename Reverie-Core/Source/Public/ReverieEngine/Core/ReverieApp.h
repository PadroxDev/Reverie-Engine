#pragma once
#include "ReverieGraphicsHandle.h"

namespace ReverieEngine::Core
{
    class ReverieApp : public ReverieGraphicsHandle
    {
    public:
        ReverieApp(int width = 1280, int height = 720, std::wstring title = L"Reverie Application");

    protected:
        virtual void OnInit() override;
        virtual void OnUpdate() override;
        virtual void OnRender() override;
        virtual void OnDestroy() override;
    };
    
}
