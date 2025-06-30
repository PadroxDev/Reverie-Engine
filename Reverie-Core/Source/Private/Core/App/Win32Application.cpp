#include "pch.h"

#include "Core/App/Win32Application.h"
#include "Core/App/BaseClientApp.h"
#include "Core/Utilities/D3D12Util.h"
#include "resources.h"

using namespace Microsoft::WRL;

using namespace ReverieEngine::Core::App;

void Win32Application::BindToClientApp(BaseClientApp* pClientApp)
{
    if(m_clientApp != nullptr)
    {
        OutputCtxDebug(L"Win32Application is already bound to a BaseClientApp instance!");
        return;
    }
    
    m_clientApp = pClientApp;
}

int Win32Application::Run(HINSTANCE hInstance, int nCmdShow)
{
    if(m_clientApp == nullptr)
    {
        OutputCtxDebug(L"Client application is null !");
        return EXIT_FAILURE; // Invalid client app
    }
    
    try
    {
        WNDCLASSEX windowClass = {};
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = WindowProc;
        windowClass.hInstance = hInstance;
     
        HICON icon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITOR));
        if (icon == NULL) {
            MessageBox(nullptr, L"TON ICONE C'EST DE LA MERDE !", L"ICONE DE CON", MB_OK | MB_ICONERROR);
        }
        windowClass.hIcon = icon;
        windowClass.hIconSm = icon;
        
        windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        windowClass.lpszClassName = L"Reverie Window Class";
        RegisterClassEx(&windowClass);

        RECT windowRect = { 0, 0, static_cast<LONG>(m_clientApp->GetWidth()), static_cast<LONG>(m_clientApp->GetHeight()) };
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

        // Calculate the position to center the window on the screen.
        const int windowWidth = windowRect.right - windowRect.left;
        const int windowHeight = windowRect.bottom - windowRect.top;

        const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        
        const int x = (screenWidth - windowWidth) / 2;
        const int y = (screenHeight - windowHeight) / 2;
        
        m_hwnd = CreateWindow(
            windowClass.lpszClassName,
            m_clientApp->GetWindowTitle(),
            m_kWindowStyle,
            x,
            y,
            windowRect.right - windowRect.left,
            windowRect.bottom - windowRect.top,
            nullptr,
            nullptr,
            hInstance,
            this
        );

        m_clientApp->OnInit();
    
        ShowWindow(m_hwnd, nCmdShow);
        
        // Main loop
        MSG msg = {};
        while(msg.message != WM_QUIT)
        {
            // Process any messages in the queue.
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        m_clientApp->OnDestroy();

        return static_cast<char>(msg.wParam);
    }
    catch(const std::exception& e)
    {
        OutputCtxDebug(L"ReverieWindowHandle::Run - Exception:");
        OutputDebugStringA(e.what());
        OutputDebugString(L"/nTerminating./n");

        m_clientApp->OnDestroy();
        return EXIT_FAILURE;
    }
}

void Win32Application::SetFullscreenMode(const FullscreenMode mode)
{
    if (mode == m_currentFullscreenMode)
        return; // Already in this mode
    
    auto pSwapChain = m_clientApp->GetSwapChain();
    
    switch(mode) {
    case FullscreenMode::Borderless:
        {
            // Save the old window rect so we can restore it when exiting fullscreen mode.
            GetWindowRect(m_hwnd, &m_windowRect);

            // Make the window borderless so that the client area can fill the screen.
            SetWindowLong(m_hwnd, GWL_STYLE, m_kWindowStyle & ~(WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME));

            RECT fullscreenWindowRect;
            try
            {
                if (pSwapChain)
                {
                    // Get the settings of the display on which the app's window is currently displayed
                    ComPtr<IDXGIOutput> pOutput;
                    ThrowIfFailed(pSwapChain->GetContainingOutput(&pOutput));
                    DXGI_OUTPUT_DESC Desc;
                    ThrowIfFailed(pOutput->GetDesc(&Desc));
                    fullscreenWindowRect = Desc.DesktopCoordinates;
                }
                else
                {
                    // Fallback to EnumDisplaySettings implementation
                    throw HrException(S_FALSE);
                }
            }
            catch (HrException& e)
            {
                UNREFERENCED_PARAMETER(e);

                // Get the settings of the primary display
                DEVMODE devMode = {};
                devMode.dmSize = sizeof(DEVMODE);
                EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &devMode);

                fullscreenWindowRect = {
                    devMode.dmPosition.x,
                    devMode.dmPosition.y,
                    devMode.dmPosition.x + static_cast<LONG>(devMode.dmPelsWidth),
                    devMode.dmPosition.y + static_cast<LONG>(devMode.dmPelsHeight)
                };
            }

            SetWindowPos(
                m_hwnd,
                HWND_TOP, // Could be TOPMOST
                fullscreenWindowRect.left,
                fullscreenWindowRect.top,
                fullscreenWindowRect.right,
                fullscreenWindowRect.bottom,
                SWP_FRAMECHANGED | SWP_NOACTIVATE
            );

            ShowWindow(m_hwnd, SW_MAXIMIZE);
        }
        break;
    case FullscreenMode::Windowed:
        {
            // Restore the window's attributes and size.
            SetWindowLong(m_hwnd, GWL_STYLE, m_kWindowStyle);

            SetWindowPos(
                m_hwnd,
                HWND_NOTOPMOST,
                m_windowRect.left,
                m_windowRect.top,
                m_windowRect.right - m_windowRect.left,
                m_windowRect.bottom - m_windowRect.top,
                SWP_FRAMECHANGED | SWP_NOACTIVATE);

            ShowWindow(m_hwnd, SW_NORMAL);
        }
        break;
    }

    m_currentFullscreenMode = mode;
}

void Win32Application::ToggleFullscreenMode()
{
    FullscreenMode newMode = m_currentFullscreenMode == FullscreenMode::Windowed ? FullscreenMode::Borderless : FullscreenMode::Windowed;
    SetFullscreenMode(newMode);
}

void Win32Application::SetWindowZOrderToTopMost(const BOOL bSetToTopMost)
{
    RECT windowRect;
    GetWindowRect(m_hwnd, &windowRect);
    
    SetWindowPos(
        m_hwnd,
        (bSetToTopMost) ? HWND_TOPMOST : HWND_NOTOPMOST,
        windowRect.left,
        windowRect.top,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        SWP_FRAMECHANGED | SWP_NOACTIVATE
    );
}

Win32Application::Win32Application() :
    m_hwnd(nullptr),
    m_windowRect({}),
    m_currentFullscreenMode(FullscreenMode::Windowed),
    m_clientApp(nullptr)
{ }

LRESULT Win32Application::WindowProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
    Win32Application* win32App = reinterpret_cast<Win32Application*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    BaseClientApp* clientApp = (win32App != nullptr) ? win32App->GetClientApp() : nullptr;
    
    switch(message)
    {
    case WM_CREATE:
        {
            // Save the DXSample* passed in to CreateWindow.
            LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
        }
        return 0;

    case WM_SYSKEYDOWN:
        // Handle ALT+ENTER:
            if ((wParam == VK_RETURN) && (lParam & (1 << 29)))
            {
                if (clientApp && clientApp->GetDeviceResources()->IsTearingSupported())
                {
                    // Loop through fullscreen modes and toggle between them.
                    win32App->ToggleFullscreenMode();
                    return 0;
                }
                return 0;
            }
        // Send all other WM_SYSKEYDOWN messages to the default WndProc.
        break;
    case WM_SYSCHAR:
        if (wParam == VK_RETURN)
        {
            return 0; // Prevent system beep on Alt+Enter
        }
        break;
    case WM_PAINT:
        if (clientApp != nullptr)
        {
            clientApp->OnUpdate();
            clientApp->OnRender();
        }
        return 0;

    case WM_SIZE:
        if(clientApp != nullptr)
        {
            RECT windowRect = {};
            GetWindowRect(hWnd, &windowRect);
            clientApp->SetWindowBounds(windowRect);

            RECT clientRect = {};
            GetClientRect(hWnd, &clientRect);
            clientApp->OnWindowSizeChanged(
                clientRect.right - clientRect.left,
                clientRect.bottom - clientRect.top,
                wParam == SIZE_MINIMIZED
            );
        }
        return 0;

    case WM_MOVE:
        if(clientApp != nullptr)
        {
            RECT windowRect = {};
            GetWindowRect(hWnd, &windowRect);
            clientApp->SetWindowBounds(windowRect);

            int xPos = (int)(short)LOWORD(lParam);
            int yPos = (int)(short)HIWORD(lParam);
            clientApp->OnWindowMoved(xPos, yPos);
        }
        return 0;

    case WM_DISPLAYCHANGE:
        if(clientApp != nullptr)
        {
            clientApp->OnDisplayChanged();
        }
        return 0;
        
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    // Handle any messages the switch statement didn't.
    return DefWindowProc(hWnd, message, wParam, lParam);
}