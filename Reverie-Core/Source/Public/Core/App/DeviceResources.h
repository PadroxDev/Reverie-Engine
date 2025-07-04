﻿#pragma once

using namespace Microsoft::WRL;

namespace ReverieEngine
{
    // Forward declarations
    class Win32Application;

    namespace Core
    {
        // Provides an interface for an application that owns DeviceResources to be notified of the device being lost or created.
        interface IDeviceNotify
        {
            virtual void OnDeviceLost() = 0;
            virtual void OnDeviceRestored() = 0;
        };

        struct DeviceConfig
        {
            bool vsyncEnabled = true;
            DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
            DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D32_FLOAT;
            UINT backBufferCount = 2;
            D3D_FEATURE_LEVEL minFeatureLevel = D3D_FEATURE_LEVEL_11_0;
            UINT flags = 0; // Use DX::DeviceResources::c_AllowTearing, etc.
            UINT adapterIDoverride = UINT_MAX;
        };
        
        // Controls all the DirectX device resources.
        class DeviceResources
        {
            DeviceResources() {}
        public:
            static const unsigned int c_AllowTearing = 0x1;
            static const unsigned int c_RequireTearingSupport = 0x2;

            DeviceResources(
                Win32Application* win32App,
                const DeviceConfig& config
            );
            ~DeviceResources();

            void InitializeDXGIAdapter();
            void SetAdapterOverride(UINT adapterID) { m_adapterIDoverride = adapterID; }
            void SetVSyncEnabled(bool bEnabled) { m_vsyncEnabled = bEnabled; }
            void CreateDeviceResources();
            void CreateWindowSizeDependentResources();
            void SetWindow(HWND window, int width, int height);
            bool WindowSizeChanged(int width, int height, bool minimized);
            void HandleDeviceLost();
            void RegisterDeviceNotify(IDeviceNotify* pDeviceNotify)
            { 
                m_deviceNotify = pDeviceNotify; 

                // On RS4 and higher, applications that handle device removal 
                // should declare themselves as being able to do so
                __if_exists(DXGIDeclareAdapterRemovalSupport)
                {
                    if (pDeviceNotify)
                    {
                        if (FAILED(DXGIDeclareAdapterRemovalSupport()))
                        {
                            OutputDebugString(L"Warning: application failed to declare adapter removal support.\n");
                        }
                    }
                }
            }

            void Prepare(D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_PRESENT);
            void Present(D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_RENDER_TARGET);
            void ExecuteCommandList();
            void WaitForGpu() noexcept;

            // Device Accessors.
            RECT GetOutputSize() const { return m_outputSize; }
            bool IsWindowVisible() const { return m_isWindowVisible; }
            bool IsTearingSupported() const { return m_options & c_AllowTearing; }

            // Direct3D Accessors.
            IDXGIAdapter1*              GetAdapter() const { return m_adapter.Get(); }
            ID3D12Device*               GetD3DDevice() const { return m_d3dDevice.Get(); }
            IDXGIFactory4*              GetDXGIFactory() const { return m_dxgiFactory.Get(); }
            IDXGISwapChain3*            GetSwapChain() const { return m_swapChain.Get(); }
            D3D_FEATURE_LEVEL           GetDeviceFeatureLevel() const { return m_d3dFeatureLevel; }
            ID3D12Resource*             GetRenderTarget() const { return m_renderTargets[m_backBufferIndex].Get(); }
            ID3D12Resource*             GetDepthStencil() const { return m_depthStencil.Get(); }
            ID3D12CommandQueue*         GetCommandQueue() const { return m_commandQueue.Get(); }
            ID3D12CommandAllocator*     GetCommandAllocator() const { return m_commandAllocators[m_backBufferIndex].Get(); }
            ID3D12GraphicsCommandList*  GetCommandList() const { return m_commandList.Get(); }
            DXGI_FORMAT                 GetBackBufferFormat() const { return m_backBufferFormat; }
            DXGI_FORMAT                 GetDepthBufferFormat() const { return m_depthBufferFormat; }
            D3D12_VIEWPORT              GetScreenViewport() const { return m_screenViewport; }
            D3D12_RECT                  GetScissorRect() const { return m_scissorRect; }
            UINT                        GetCurrentFrameIndex() const { return m_backBufferIndex; }
            UINT                        GetPreviousFrameIndex() const { return m_backBufferIndex == 0 ? m_backBufferCount - 1 : m_backBufferIndex - 1; }
            UINT                        GetBackBufferCount() const { return m_backBufferCount; }
            unsigned int                GetDeviceOptions() const { return m_options; }
            LPCWSTR                     GetAdapterDescription() const { return m_adapterDescription.c_str(); }
            UINT                        GetAdapterID() const { return m_adapterID; }
            bool                        IsVSyncEnabled() const { return m_vsyncEnabled; }

            CD3DX12_CPU_DESCRIPTOR_HANDLE GetRenderTargetView() const
            {
                return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), m_backBufferIndex, m_rtvDescriptorSize);
            }
            CD3DX12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const
            {
                return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
            }

        private:
            void MoveToNextFrame();
            void InitializeAdapter(IDXGIAdapter1** ppAdapter);

            const static size_t MAX_BACK_BUFFER_COUNT = 3;

            UINT                                                m_adapterIDoverride;
            UINT                                                m_backBufferIndex;
            ComPtr<IDXGIAdapter1>                               m_adapter;
            UINT                                                m_adapterID;
            std::wstring                                        m_adapterDescription;

            // Direct3D objects.
            ComPtr<ID3D12Device>                                m_d3dDevice;
            ComPtr<ID3D12CommandQueue>                          m_commandQueue;
            ComPtr<ID3D12GraphicsCommandList>                   m_commandList;
            ComPtr<ID3D12CommandAllocator>                      m_commandAllocators[MAX_BACK_BUFFER_COUNT];

            // Swap chain objects.
            ComPtr<IDXGIFactory4>                               m_dxgiFactory;
            ComPtr<IDXGISwapChain3>                             m_swapChain;
            ComPtr<ID3D12Resource>                              m_renderTargets[MAX_BACK_BUFFER_COUNT];
            ComPtr<ID3D12Resource>                              m_depthStencil;

            // Presentation fence objects.
            ComPtr<ID3D12Fence>                                 m_fence;
            UINT64                                              m_fenceValues[MAX_BACK_BUFFER_COUNT];
            Wrappers::Event                                     m_fenceEvent;

            // Direct3D rendering objects.
            ComPtr<ID3D12DescriptorHeap>                        m_rtvDescriptorHeap;
            ComPtr<ID3D12DescriptorHeap>                        m_dsvDescriptorHeap;
            UINT                                                m_rtvDescriptorSize;
            D3D12_VIEWPORT                                      m_screenViewport;
            D3D12_RECT                                          m_scissorRect;

            // Direct3D properties.
            DXGI_FORMAT                                         m_backBufferFormat;
            DXGI_FORMAT                                         m_depthBufferFormat;
            UINT                                                m_backBufferCount;
            D3D_FEATURE_LEVEL                                   m_d3dMinFeatureLevel;

            // Cached device properties.
            HWND                                                m_window;
            D3D_FEATURE_LEVEL                                   m_d3dFeatureLevel;
            RECT                                                m_outputSize;
            bool                                                m_isWindowVisible;

            // Win32
            Win32Application*                                   m_win32App;
            
            // DeviceResources options (see flags above)
            unsigned int                                        m_options;
            bool                                                m_bTearingSupported;
            bool                                                m_vsyncEnabled;

            // The IDeviceNotify can be held directly as it owns the DeviceResources.
            IDeviceNotify*                                      m_deviceNotify;
        };
    }
}