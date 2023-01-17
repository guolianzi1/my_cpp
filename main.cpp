//
// Created by wujin on 2023/1/16.
//
#include "iostream"
#include <sources/tools/HTTPRequest.hpp>
#include <sources/utils/registry_util.hpp>
#include "gtest/gtest.h"

TEST(RegistryTest, test1){
    LPCSTR key_path = R"(SOFTWARE\Microsoft\Windows\CurrentVersion\rpa_client\rpa_test)";
    LPCWSTR value_name = L"a1定定位嘎嘎嘎位";
    LPCWSTR value = L"赶紧你看好你看谈话内容和同龄人你乱扔11144111";

    auto r = registry_util_1::get_key_value(key_path, value_name);
    std::cout << r << std::endl;
}


TEST(NetWorkTest, test1){
    LPCWSTR filepath = L"D:\\系统下载\\zd_01_1\\sky.jpg";
    bool result = http::URLDownloadToFileW(L"http://127.0.0.1:5000/download/5", filepath);
    if (result){
        std::cout << "done" << std::endl;
    } else{
        std::cout << "download error" << std::endl;
    }
}

int main(int argc, char **args){
    testing::InitGoogleTest(&argc, args);
    return RUN_ALL_TESTS();
}