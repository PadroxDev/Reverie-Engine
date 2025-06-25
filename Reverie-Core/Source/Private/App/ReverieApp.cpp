#include "ReverieEngine/App/ReverieApp.h"

#include "ReverieEngine/App/BaseClientApp.h"
#include "ReverieEngine/App/Win32Application.h"
#include "ReverieEngine/Util/DebugUtil.h"

using namespace ReverieEngine::App;
using namespace DX;

std::unique_ptr<ReverieApp> ReverieApp::CreateWithWin32(UINT width, UINT height, const std::wstring& title,
    std::unique_ptr<Win32Application>* outWin32App)
{
    auto app = std::make_unique<ReverieApp>(width, height, std::move(title));
    auto win32 = std::make_unique<Win32Application>();

    app->BindToWin32App(win32.get());
    win32->BindToClientApp(app.get());
    
    if(outWin32App)
        *outWin32App = std::move(win32);
        
    return app;
}

void ReverieApp::OnDeviceLost()
{ }

void ReverieApp::OnDeviceRestored()
{ }

void ReverieApp::OnInit()
{
    m_deviceResources = std::make_unique<DeviceResources>(
        m_win32App,
        DXGI_FORMAT_R8G8B8A8_UNORM,
        DXGI_FORMAT_UNKNOWN,
        k_FrameCount,
        D3D_FEATURE_LEVEL_11_0,
        DeviceResources::c_RequireTearingSupport,
        m_adapterIDoverride
    );

    m_deviceResources->RegisterDeviceNotify(this);
    m_deviceResources->SetWindow(m_win32App->GetHwnd(), m_width, m_height);
    m_deviceResources->InitializeDXGIAdapter();

    m_deviceResources->CreateDeviceResources();
    m_deviceResources->CreateWindowSizeDependentResources();
}

void ReverieApp::OnUpdate()
{ }

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

void ReverieApp::OnWindowSizeChanged(int width, int height, bool minimized)
{
    if(!m_deviceResources->WindowSizeChanged(width, height, minimized))
    {
        return;
    }

    UpdateForSizeChange(width, height);
}
