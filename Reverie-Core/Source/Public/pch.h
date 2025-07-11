﻿#pragma once

#pragma warning(disable:4201) // nonstandard extension used : nameless struct/union
#pragma warning(disable:4238) // nonstandard extension used : class rvalue used as lvalue
#pragma warning(disable:4239) // A non-const reference may only be bound to an lvalue; assignment operator takes a reference to non-const
#pragma warning(disable:4324) // structure was padded due to __declspec(align())

#include <winsdkver.h>
#define _WIN32_WINNT 0x0A00
#include <sdkddkver.h>

// Use the C++ standard templated min/max
#define NOMINMAX

// DirectX apps don't need GDI
#define NODRAWTEXT
#define NOBITMAP

// Include <mcx.h> if you need this
#define NOMCX

// Include <winsvc.h> if you need this
#define NOSERVICE

// WinHelp is deprecated
#define NOHELP

// Exclude rarely-used stuff from Windows headers.
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <wrl/client.h>
#include <wrl/event.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include "Core/d3dx12.h"
#include <DirectXMath.h>
#include <D3Dcompiler.h>
#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#define D3D12_GPU_VIRTUAL_ADDRESS_NULL      ((D3D12_GPU_VIRTUAL_ADDRESS)0)
#define D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN   ((D3D12_GPU_VIRTUAL_ADDRESS)-1)
#define MY_IID_PPV_ARGS                     IID_PPV_ARGS

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdarg>
#include <vector>
#include <memory>
#include <string>
#include <cwctype>
#include <exception>
#include <stdexcept>
#include <format>
#include <numbers>
#include <limits>

#include <ppltasks.h>
#include <functional>

#include "Core/App/DeviceResources.h"
#include "Core/Utilities/DebugUtil.h"