#ifndef MY_CPP_REGISTRY_UTIL_HPP
#define MY_CPP_REGISTRY_UTIL_HPP

#if defined(_WIN32) || defined(__CYGWIN__)
#include <Windows.h>
#include <iostream>
#include <string>
#include <./string_util.hpp>

namespace registry_util_1{
    class RegError : public std::exception {
    public:
        explicit RegError(const char *brief_error_message) : std::exception(brief_error_message) {
            this->brief_error_message = std::string(brief_error_message);
        }

        RegError(const RegError &old) noexcept: std::exception(old) {
            this->brief_error_message = old.brief_error_message;
        }

        ~RegError() override = default;

        const char *what() const override {
            return this->brief_error_message.c_str();
        }

        std::string brief_error_message;
    };


    void add_key_value(LPCSTR key_path, LPCWSTR value_name, LPCWSTR text, unsigned long size,
                       HKEY root_key = HKEY_CURRENT_USER) {
        HKEY result;
        auto status = RegOpenKey(root_key, key_path, &result);
        if (status != ERROR_SUCCESS) {
            throw RegError("not exits!");
        } else {
            RegSetValueExW(result, value_name, 0, REG_SZ,
                           reinterpret_cast<const BYTE *>(text), size + 1);
            RegCloseKey(result);
        }
    }


    std::string get_key_value(LPCSTR key_path, LPCWSTR value_name, HKEY root_key = HKEY_CURRENT_USER) {
        HKEY hResult;
        auto status = RegOpenKey(root_key, key_path, &hResult);
        if (status != ERROR_SUCCESS) {
            throw RegError("not exits!");
        } else {
            wchar_t buff[255] = {0};
            DWORD buff_size = sizeof(buff);
            RegQueryValueExW(
                    hResult,
                    value_name,
                    nullptr, nullptr, reinterpret_cast<LPBYTE>(&buff), &buff_size);
            RegCloseKey(hResult);
            std::wstring ws1(buff);
            return string_util_1::wstring_to_string(65001, ws1);
        }
    }

}
#endif

#endif //MY_CPP_REGISTRY_UTIL_HPP
