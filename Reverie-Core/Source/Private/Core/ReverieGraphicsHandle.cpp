#include "Core/ReverieGraphicsHandle.h"

#include <wrl/client.h>

#include <utility>

#include "stdafx.h"
#include "Util/D3D12Util.h"
#include "Util/HResultUtil.h"

using namespace ReverieEngine::Util;
using Microsoft::WRL::ComPtr;

namespace ReverieEngine::Core
{
    ReverieGraphicsHandle::ReverieGraphicsHandle(int width, int height, std::wstring title) : ReverieWindowHandle(width,
        height, std::move(title))
    {}
    
    ReverieGraphicsHandle::~ReverieGraphicsHandle() = default;

    void ReverieGraphicsHandle::OnInit()
    {
        LoadRenderingPipeline();
    }

    void ReverieGraphicsHandle::LoadRenderingPipeline()
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

        // Describe the command queue
        D3D12_COMMAND_QUEUE_DESC queueDesc = {};
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

        // Create the command queue
        ThrowIfFailed(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue)));

        // Describe the swap chain
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    }
}
