#pragma once

#include <Windows.h>

struct IDXGIFactory1;
struct IDXGIAdapter1;

namespace ReverieEngine::Util
{
    
    void GetHardwareAdapter(
        _In_ IDXGIFactory1* pFactory,
        _Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter,
        bool requestHighPerformanceAdapter = false
    );

}
