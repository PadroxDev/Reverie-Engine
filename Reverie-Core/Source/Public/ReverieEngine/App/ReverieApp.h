#pragma once
#include "ReverieEngine/App/BaseClientApp.h"

namespace ReverieEngine::App
{
    class ReverieApp : public App::BaseClientApp
    {
    public:
        static std::unique_ptr<ReverieApp> CreateWithWin32(UINT width, UINT height, const std::wstring& title,
            std::unique_ptr<App::Win32Application>* outWin32App);

        // You should avoid using this constructor directly, use a factory method like CreateWithWin32 instead.
        ReverieApp(UINT width, UINT height, const std::wstring& title) : BaseClientApp(width, height, title)
        { }
        
        void OnInit() override;
        void OnUpdate() override;
        void OnRender() override;
        void OnDestroy() override;
    };
    
}
