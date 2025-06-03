#include "Core/ReverieWindowHandle.h"

#include "stdafx.h"
#include "Util/HResultUtil.h"

using namespace ReverieEngine::Util;

namespace ReverieEngine::Core
{
    ReverieWindowHandle::ReverieWindowHandle(INT width, INT height, const std::wstring& title)
    {
        m_width = width;
        m_height = height;
        m_aspectRatio = 0.f;
        m_title = title;

        m_bFullscreen = false;
        m_hwnd = nullptr;
        m_windowRect = {};
        m_windowBounds = {};
    }

    ReverieWindowHandle::~ReverieWindowHandle() = default;

    int ReverieWindowHandle::Run(HINSTANCE hInstance, int nCmdShow)
    {
        try
        {
            WNDCLASSEX windowClass = {};
            windowClass.cbSize = sizeof(WNDCLASSEX);
            windowClass.style = CS_HREDRAW | CS_VREDRAW;
            windowClass.lpfnWndProc = WindowProc;
            windowClass.hInstance = hInstance;
            windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
            windowClass.lpszClassName = L"Reverie Window Class";
            RegisterClassEx(&windowClass);

            RECT windowRect = { 0, 0, static_cast<LONG>(m_width), static_cast<LONG>(m_height) };
            AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
        
            m_hwnd = CreateWindow(
                windowClass.lpszClassName,
                m_title.c_str(),
                m_WindowStyle,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                windowRect.right - windowRect.left,
                windowRect.bottom - windowRect.top,
                nullptr,
                nullptr,
                hInstance,
                this
            );

            OnInit();
        
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

            OnDestroy();

            return static_cast<char>(msg.wParam);
        }
        catch(const std::exception& e)
        {
            OutputDebugString(L"ReverieWindowHandle::Run - Exception:");
            OutputDebugStringA(e.what());
            OutputDebugString(L"/nTerminating./n");

            OnDestroy();
            return EXIT_FAILURE;
        }
    }

    void ReverieWindowHandle::ToggleFullsreenWindow(IDXGISwapChain* pSwapChain)
    {
        if(m_bFullscreen)
        {
            // Restore the window's attributes and size.
            SetWindowLong(m_hwnd, GWL_STYLE, m_WindowStyle);

            SetWindowPos(
                m_hwnd,
                HWND_NOTOPMOST,
                m_windowRect.left,
                m_windowRect.top,
                m_windowRect.right - m_windowRect.left,
                m_windowRect.bottom - m_windowRect.top,
                SWP_FRAMECHANGED | SWP_NOACTIVATE
            );

            ShowWindow(m_hwnd, SW_NORMAL);
        } else
        {
            // Save the old window rect so we can restore it when exiting fullscreen mode.
            GetWindowRect(m_hwnd, &m_windowRect);

            // Make the window borderless so that the client area can fill the screen.
            SetWindowLong(m_hwnd, GWL_STYLE, m_WindowStyle & ~(WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME));

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
                HWND_TOPMOST,
                fullscreenWindowRect.left,
                fullscreenWindowRect.top,
                fullscreenWindowRect.right,
                fullscreenWindowRect.bottom,
                SWP_FRAMECHANGED | SWP_NOACTIVATE
            );


            ShowWindow(m_hwnd, SW_MAXIMIZE);
        }

        m_bFullscreen ^= true;
    }

    void ReverieWindowHandle::SetWindowZorderToTopMost(bool bSetToTopMost)
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

    LRESULT ReverieWindowHandle::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        ReverieWindowHandle* handle = reinterpret_cast<ReverieWindowHandle*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        switch (message)
        {
        case WM_CREATE:
            {
                // Save the DXSample* passed in to CreateWindow.
                LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
                SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
            }
            return 0;

        case WM_PAINT:
            if (handle)
            {
                handle->OnUpdate();
                handle->OnRender();
            }
            return 0;

        case WM_SIZE:
            if (handle)
            {
                RECT windowRect = {};
                GetWindowRect(hWnd, &windowRect);
                handle->SetWindowBounds(windowRect);

                RECT clientRect = {};
                GetClientRect(hWnd, &clientRect);
                handle->OnWindowSizeChanged(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, wParam == SIZE_MINIMIZED);
            }
            return 0;

        case WM_MOVE:
            if (handle)
            {
                RECT windowRect = {};
                GetWindowRect(hWnd, &windowRect);
                handle->SetWindowBounds(windowRect);

                int xPos = (int)(short)LOWORD(lParam);
                int yPos = (int)(short)HIWORD(lParam);
                handle->OnWindowMoved(xPos, yPos);
            }
            return 0;

        case WM_DISPLAYCHANGE:
            if (handle)
            {
                handle->OnDisplayChanged();
            }
            return 0;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }

        // Handle any messages the switch statement didn't.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    void ReverieWindowHandle::OnWindowSizeChanged(int width, int height, bool minimized)
    {
    }

    void ReverieWindowHandle::OnWindowMoved(int x, int y)
    {
    }

    void ReverieWindowHandle::OnDisplayChanged()
    {
    }

    void ReverieWindowHandle::SetWindowBounds(const RECT& rect)
    {
        m_windowBounds = rect;
    }
}
