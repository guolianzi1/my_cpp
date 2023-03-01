//
// Created by wujin on 2023/1/16.
//
#include "iostream"
#include <sources/tools/HTTPRequest.hpp>
#include <sources/utils/registry_util.hpp>
#include "gtest/gtest.h"
#include "sources/tools/configor/json.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "cargs.h"


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
    std::ifstream f1(R"(D:\Program Files\rpa\bot\bank_reconciliation\package.json)");
    auto a = json::parse(f1);
    std::cout << json::dump(a) << std::endl;
}

TEST(JsonTest, test2) {
    using json = configor::json;
    configor::value j2 = json::object({{"integer", 1}, {"float", 1.3}});
    j2["css"] = "1212";
    j2["css2"] = json::array{ 1, 2 };
    std::cout << json::dump(j2) << std::endl;
}


TEST(LoggingTest, file){
    std::string filepath(R"(F:\test\rotating.txt)");
    auto max_size = 1048576 * 5;
    auto max_files = 3;
    // 保留三个文件，每个文件5mb
    auto logger = spdlog::rotating_logger_mt(
            "client", filepath, max_size, max_files);
    // 没有行号
    logger->info("66666");
    SPDLOG_LOGGER_INFO(logger, "15 15");
    SPDLOG_LOGGER_INFO(logger, "有行号了");
}

TEST(LoggingTest, test2){
    spdlog::info("ewe");
}

TEST(LoggingTest, console_and_file){
    /*
     * 同时在控制台和文件中写入日志，像Python一样
     * */
    auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    std::string filepath(R"(E:\qct\untitled1\cmake-build-debug\rotating.txt)");
    auto max_size = 1048576 * 5;
    auto max_files = 3;
    auto file = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filepath, max_size, max_files);

//    spdlog::logger logger("multi_sink", {console, file});

    // 使用指针，因为SPDLOG_LOGGER_INFO宏要的是指针地址。如果用上面的就取地址&logger
    std::initializer_list<std::shared_ptr<spdlog::sinks::sink>> sinks{console, file};
    auto logger2 = std::make_shared<spdlog::logger>("multi_sink", sinks);

    SPDLOG_LOGGER_INFO(logger2, "控制台有吗7777");
}

static struct cag_option options[] = {
        {.identifier = 's',
                .access_letters = "s",
                .access_name = nullptr,
                .value_name = nullptr,
                .description = "Simple flag"},

        {.identifier = 'm',
                .access_letters = "mMoO",
                .access_name = nullptr,
                .value_name = nullptr,
                .description = "Multiple access letters"},

        {.identifier = 'l',
                .access_letters = nullptr,
                .access_name = "long",
                .value_name = nullptr,
                .description = "Long parameter name"},

        {.identifier = 'k',
                .access_letters = "k",
                .access_name = "key",
                .value_name = "VALUE",
                .description = "Parameter value"},

        {.identifier = 'h',
                .access_letters = "h",
                .access_name = "help",
                .description = "Shows the command help"}};

struct demo_configuration
{
    bool simple_flag;
    bool multiple_flag;
    bool long_flag;
    const char *key;
};

TEST(commandLineTest, test1){
    char identifier;
    const char *value;
    cag_option_context context;
    struct demo_configuration config = {false, false, false, NULL};

    /**
     * Now we just prepare the context and iterate over all options. Simple!
     */

    auto *a2 = new char;
    cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), 1, &a2);
    while (cag_option_fetch(&context)) {
        identifier = cag_option_get(&context);
        switch (identifier) {
            case 's':
                config.simple_flag = true;
                break;
            case 'm':
                config.multiple_flag = true;
                break;
            case 'l':
                config.long_flag = true;
                break;
            case 'k':
                value = cag_option_get_value(&context);
                config.key = value;
                break;
            case 'h':
                printf("Usage: cargsdemo [OPTION]...\n");
                printf("Demonstrates the cargs library.\n\n");
                cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
                printf("\nNote that all formatting is done by cargs.\n");
                break;
        }
    }

    std::cout << config.key << std::endl;
    delete a2;
}

int main(int argc, char **args) {
    testing::InitGoogleTest(&argc, args);
    return RUN_ALL_TESTS();
}