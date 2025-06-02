#pragma once

#include <Windows.h>

namespace ReverieEngine::Util
{
    
void ThrowIfFailedImp(HRESULT hr, const char* file, int line, const char* expression);

#define ThrowIfFailed(expr) ThrowIfFailedImp((expr), __FILE__, __LINE__, #expr)

}
