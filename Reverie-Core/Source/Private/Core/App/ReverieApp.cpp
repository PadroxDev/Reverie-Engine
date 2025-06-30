#include "pch.h"
#include "Core/App/ReverieApp.h"

#include "Core/App/Win32Application.h"
#include "Core/App/GameTimer.h"

using namespace ReverieEngine;

std::unique_ptr<ReverieApp> ReverieApp::CreateWithWin32(const UINT width, const UINT height,
    const std::wstring& title, std::unique_ptr<Win32Application>* ppOutWin32App)
{
    auto app = std::make_unique<ReverieApp>(width, height, std::move(title));
    auto win32 = std::make_unique<Win32Application>();

    app->BindToWin32App(win32.get());
    win32->BindToClientApp(app.get());
    
    if(ppOutWin32App)
        *ppOutWin32App = std::move(win32);
        
    return app;
}

void ReverieApp::OnDeviceLost()
{ }

void ReverieApp::OnDeviceRestored()
{ }

void ReverieApp::OnInit()
{
    Core::DeviceConfig config;
    config.vsyncEnabled = false;
    config.backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    config.depthBufferFormat = DXGI_FORMAT_UNKNOWN;
    config.backBufferCount = k_FrameCount;
    config.minFeatureLevel = D3D_FEATURE_LEVEL_11_0;
    config.flags = Core::DeviceResources::c_AllowTearing;
    config.adapterIDoverride = m_adapterIDoverride;
    
    m_deviceResources = std::make_unique<Core::DeviceResources>(m_win32App, config);
    m_deviceResources->RegisterDeviceNotify(this);
    m_deviceResources->SetWindow(m_win32App->GetHwnd(), m_width, m_height);
    m_deviceResources->InitializeDXGIAdapter();

    m_deviceResources->CreateDeviceResources();
    m_deviceResources->CreateWindowSizeDependentResources();

    m_gameTimer = std::make_unique<Core::GameTimer>();
    m_gameTimer->Initialize();
}

void ReverieApp::OnUpdate()
{
    m_gameTimer->Tick();
}

void ReverieApp::OnRender()
{
    m_deviceResources->Prepare(D3D12_RESOURCE_STATE_PRESENT);

    auto commandList = m_deviceResources->GetCommandList();
    auto rtvHandle = m_deviceResources->GetRenderTargetView();

    // Clear the render target view.
    commandList->ClearRenderTargetView(rtvHandle, m_clearColor, 0, nullptr);

    // Clear the depth stencil view if it exists.
    if (m_deviceResources->GetDepthBufferFormat() != DXGI_FORMAT_UNKNOWN)
    {
        auto dsvHandle = m_deviceResources->GetDepthStencilView();
        commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
    }
    
    m_deviceResources->Present(D3D12_RESOURCE_STATE_RENDER_TARGET);
}

void ReverieApp::OnDestroy()
{ }

void ReverieApp::OnWindowSizeChanged(const int width, const int height, const bool bMinimized)
{
    if(!m_deviceResources->WindowSizeChanged(width, height, bMinimized))
    {
        return;
    }

    UpdateForSizeChange(width, height);
}
