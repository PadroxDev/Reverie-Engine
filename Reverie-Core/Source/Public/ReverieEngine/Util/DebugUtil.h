#pragma once

#include <filesystem>

namespace ReverieEngine::Util
{
    // Helper to extract filename without extension
    inline std::wstring GetFileBaseName(const char* filePath) {
        std::filesystem::path p(filePath);
        return p.stem().wstring();  // returns filename without extension
    }

    //
    // 🧩 Helper: Convert UTF-8 std::string to std::wstring
    //
    inline std::wstring Utf8ToWide(const std::string& str) {
        int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
        std::wstring wide(len, L'\0');
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wide[0], len);
        wide.resize(wcslen(wide.c_str())); // trim null terminator
        return wide;
    }
    
    inline void OutputContextDebugImp(const char* file, const char* func, const std::wstring& msg) {
        std::wstring className = GetFileBaseName(file);
        std::wstring functionName(func, func + strlen(func)); // simple ASCII-safe conversion

        std::wstring fullMsg = L"[" + className + L"." + functionName + L"]: " + msg + L"/n";
        OutputDebugString(fullMsg.c_str());
    }

    inline void OutputContextDebugImp(const char* file, const char* func, const std::string& msg) {
        OutputContextDebugImp(file, func, Utf8ToWide(msg));
    }
    
#define OutputCtxDebug(msg) OutputContextDebugImp(__FILE__, __func__, msg)
    
}
