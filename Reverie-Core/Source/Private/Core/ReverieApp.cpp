#include "Core/ReverieApp.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl/client.h>

#include "Core/Core.h"
#include "Util/D3D12Util.h"
#include "Util/ErrorUtil.h"

using namespace ReverieEngine::Util;
using Microsoft::WRL::ComPtr;

namespace ReverieEngine::Core
{
    ReverieApp::ReverieApp(float width, float height, const char* name)
    {
    }

    ReverieApp::~ReverieApp()
    = default;

    void ReverieApp::Initialize()
    {
        LoadPipeline();
    }

    void ReverieApp::LoadPipeline()
    {
        // If debugging, enable the debug layer
#if defined(DEBUG) || defined(_DEBUG)
        ComPtr<ID3D12Debug> debugController;
        if(SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
        {
            debugController->EnableDebugLayer();
        }
#endif

        // Create the factory
        ComPtr<IDXGIFactory4> factory;
        ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&factory)));
        
        // Attempt to create a hardware device which will almost always succeed
        ComPtr<IDXGIAdapter1> hardwareAdapter;
        GetHardwareAdapter(factory.Get(), &hardwareAdapter, true);
        
        HRESULT hardwareDeviceResult = D3D12CreateDevice(
            hardwareAdapter.Get(),
            D3D_FEATURE_LEVEL_11_0,
            IID_PPV_ARGS(&m_device)
        );

        // Fallback to a warp device
        if(FAILED(hardwareDeviceResult))
        {
            ComPtr<IDXGIAdapter> warpAdapter;
            ThrowIfFailed(factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)));
            
            ThrowIfFailed(D3D12CreateDevice(
                warpAdapter.Get(),
                D3D_FEATURE_LEVEL_11_0,
                IID_PPV_ARGS(&m_device)
            ));
        }
    }
}
