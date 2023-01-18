//
// Created by wujin on 2023/1/16.
//
#include "iostream"
#include <sources/tools/HTTPRequest.hpp>
#include <sources/utils/registry_util.hpp>
#include "gtest/gtest.h"
#include "sources/tools/configor/json.hpp"


TEST(RegistryTest, test1) {
    LPCSTR key_path = R"(SOFTWARE\Microsoft\Windows\CurrentVersion\rpa_client\rpa_test)";
    LPCWSTR value_name = L"a1定定位嘎嘎嘎位";
    LPCWSTR value = L"赶紧你看好你看谈话内容和同龄人你乱扔11144111";

    auto r = registry_util_1::get_key_value(key_path, value_name);
    std::cout << r << std::endl;
}


TEST(NetWorkTest, test1) {
    LPCWSTR filepath = L"D:\\系统下载\\zd_01_1\\sky.jpg";
    bool result = http::URLDownloadToFileW(L"http://127.0.0.1:5000/download/5", filepath);
    if (result) {
        std::cout << "done" << std::endl;
    } else {
        std::cout << "download error" << std::endl;
    }
}


TEST(NetWorkTest, test2) {
    http::Request request("http://127.0.0.1:5000");
    auto response = request.send("GET");
    std::string r(response.body.cbegin(), response.body.cend());
    std::cout << r << std::endl;
}


TEST(JsonTest, test1) {
    using json = configor::json;
    configor::value j2 = json::object({{"integer", 1}, {"float", 1.3}});
    j2["css"] = "1212";
    j2["css2"] = json::array{ 1, 2 };

    std::ifstream f1(R"(D:\Program Files\rpa\bot\bank_reconciliation\package.json)");
    auto a = json::parse(f1);
    std::cout << json::dump(a) << std::endl;

    std::cout << json::dump(j2) << std::endl;
}


int main(int argc, char **args) {
    testing::InitGoogleTest(&argc, args);
    return RUN_ALL_TESTS();
}