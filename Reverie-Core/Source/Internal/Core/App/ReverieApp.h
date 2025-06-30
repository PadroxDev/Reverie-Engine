#pragma once
#include "Core/App/BaseClientApp.h"

namespace ReverieEngine::Core::App
{
    class GameTimer;

    class ReverieApp : public BaseClientApp
    {
    public:
        static std::unique_ptr<ReverieApp> CreateWithWin32(UINT width, UINT height, const std::wstring& title,
                                                           std::unique_ptr<Win32Application>* ppOutWin32App);

        // You should avoid using this constructor directly, use a factory method like CreateWithWin32 instead.
        ReverieApp(UINT width, UINT height, const std::wstring& title) : BaseClientApp(width, height, title)
        { }

        // IDeviceNotify
        void OnDeviceLost() override;
        void OnDeviceRestored() override;
        
        void OnInit() override;
        void OnUpdate() override;
        void OnRender() override;
        void OnDestroy() override;
        void OnWindowSizeChanged(int width, int height, bool minimized) override;

        // Accessors
        GameTimer* GetGameTimer() const { return m_gameTimer.get(); }
        
    protected:
        std::unique_ptr<GameTimer> m_gameTimer;
    
    private:
        static constexpr UINT k_FrameCount = 3; // Buffering: triple buffering

        float m_clearColor[4] = { 0.05f, 0.05f, 0.15f, 1.0f }; // Dark navy blue
    };
}
