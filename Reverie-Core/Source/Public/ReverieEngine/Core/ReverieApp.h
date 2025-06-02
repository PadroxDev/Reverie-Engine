#pragma once

#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class ID3D12Device;
struct IDXGIFactory1;
struct IDXGIAdapter1;

namespace ReverieEngine::Core
{
    class ReverieApp
    {
    public:
        ReverieApp(float width, float height, const char* name);
        ~ReverieApp();

        void Initialize();

    private:
        void LoadPipeline();

        ComPtr<ID3D12Device> m_device;
    };
   
}
