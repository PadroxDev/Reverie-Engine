#include "Util/ErrorUtil.h"
#include <stdexcept>
#include <string>
#include <sstream>
#include <comdef.h>

namespace ReverieEngine::Util
{
    
    inline std::string NarrowFromWide(const wchar_t* wstr)
    {
        int len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
        std::string result(len, 0);
        WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &result[0], len, nullptr, nullptr);
        result.pop_back(); // remove null terminator
        return result;
    }

    void ThrowIfFailedImp(HRESULT hr, const char* file, int line, const char* expression)
    {
        if (FAILED(hr))
        {
            _com_error err(hr);
            std::ostringstream oss;
            oss << "HRESULT failed (0x" << std::hex << hr << "): "
                << NarrowFromWide(err.ErrorMessage()) << "\n"
                << "  at " << file << ":" << line << "\n"
                << "  Expression: " << expression;
            throw std::runtime_error(oss.str());
        }
    }

}
