#pragma once

#include <wrl/client.h>

#include "ReverieWindowHandle.h"

using Microsoft::WRL::ComPtr;

struct ID3D12Device;
struct ID3D12CommandQueue;

namespace ReverieEngine::Core
{
    class ReverieGraphicsHandle : public ReverieWindowHandle
    {
    public:
        ReverieGraphicsHandle(int width = 1280, int height = 720, std::wstring title = L"Reverie Graphics Window");
        virtual ~ReverieGraphicsHandle() override;
        ReverieGraphicsHandle(const ReverieGraphicsHandle&) = default;
        ReverieGraphicsHandle& operator=(const ReverieGraphicsHandle&) = delete;
        ReverieGraphicsHandle(ReverieGraphicsHandle&&) = default;
        ReverieGraphicsHandle& operator=(ReverieGraphicsHandle&&) = delete;

    protected:
        virtual void OnInit() override;
        virtual void OnUpdate() override = 0;
        virtual void OnRender() override = 0;
        virtual void OnDestroy() override = 0;
        
    private:
        void LoadRenderingPipeline();
        
        ComPtr<ID3D12Device> m_device;
        ComPtr<ID3D12CommandQueue> m_commandQueue;
    };
   
}
