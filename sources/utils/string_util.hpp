//
// Created by wujin on 2023/1/16.
//

#ifndef MY_CPP_STRING_UTIL_HPP
#define MY_CPP_STRING_UTIL_HPP
#if defined(_WIN32) || defined(__CYGWIN__)
#include <string>
#include <iostream>
#include <locale>
#include <windows.h>
#include <fstream>

namespace string_util_1{

    std::string translateStrCodePage(unsigned int codepageFrom, const std::string &strFrom, unsigned int codepageTo){
        // 计算字符串所需空间大小
        int len = MultiByteToWideChar(codepageFrom, 0, strFrom.c_str(), -1, nullptr, 0);

        auto *wStr = new wchar_t[len + 1];
        memset(wStr, 0, len + 1);

        // 转换为宽字符
        MultiByteToWideChar(codepageFrom, 0, strFrom.c_str(), -1, wStr, len);

        // 计算从codepageFrom到codepageTo的所需空间大小
        len = WideCharToMultiByte(codepageTo, 0, wStr, -1, nullptr, 0, nullptr, nullptr);
        char* str = new char[len + 1];
        memset(str, 0, len + 1);

        // 转换
        WideCharToMultiByte(codepageTo, 0, wStr, -1, str, len, nullptr, nullptr);
        std::string strTo(str);

        delete[] wStr;
        delete[] str;

        return strTo;
    }

    std::wstring translateStrToWStr(unsigned int codepage, const std::string &strFrom){
        // 计算字符串所需空间大小
        int len = MultiByteToWideChar(codepage, 0, strFrom.c_str(), -1, nullptr, 0);

        auto *wStr = new wchar_t[len + 1];
        memset(wStr, 0, len + 1);

        // 转换为宽字符
        MultiByteToWideChar(codepage, 0, strFrom.c_str(), -1, wStr, len);

        std::wstring strTo(wStr);

        delete[] wStr;

        return strTo;
    }

    std::string wstring_to_string(unsigned long ToPage, const std::wstring &string1) {
        std::string result;
        //获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的
        int len = WideCharToMultiByte(
                ToPage,
                0,
                string1.c_str(),
                (int)string1.size(),
                nullptr, 0, nullptr, nullptr);

        char *buffer = new char[len + 1];
        //宽字节编码转换成多字节编码
        WideCharToMultiByte(
                ToPage,
                0,
                string1.c_str(),
                (int)string1.size(),
                buffer, len, nullptr, nullptr);

        buffer[len] = '\0';
        //删除缓冲区并返回值
        result.append(buffer);
        delete[] buffer;
        return result;
    }

    std::wstring string_to_wstring(const std::string &string1) {
        std::wstring result;
        //获取缓冲区大小，并申请空间，缓冲区大小按字符计算
        int len = MultiByteToWideChar(
                CP_ACP,
                0,
                string1.c_str(), static_cast<int>(string1.size()), nullptr, 0);
        auto *buffer = new wchar_t[len + 1];
        //多字节编码转换成宽字节编码
        MultiByteToWideChar(
                CP_ACP,
                0,
                string1.c_str(), (int)string1.size(), buffer, len);

        buffer[len] = '\0';             //添加字符串结尾
        //删除缓冲区并返回值
        result.append(buffer);
        delete[] buffer;
        return result;
    }
}

#endif
#endif