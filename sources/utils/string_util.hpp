#include <string>
#include <iostream>
#include <locale>
#include <windows.h>
#include <fstream>

std::string translateStrCodePage(unsigned int codepageFrom, const std::string &strFrom, unsigned int codepageTo)
{
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

std::wstring translateStrToWStr(unsigned int codepage, const std::string &strFrom)
{
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