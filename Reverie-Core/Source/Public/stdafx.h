﻿//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently.

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers.
#endif

#include <windows.h>

#include <dxgi1_6.h>
#include <d3d12.h>
#include <d2d1_3.h>
#include <dwrite.h>
#include <d3d11on12.h>
#include <DirectXMath.h>

#include <wrl.h>
#include <string>
#include <vector>
#include <memory>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#include "d3dx12.h"
#include "ReverieEngine/App/DeviceResources.h"
#include "ReverieEngine/Util/D3D12Util.h"