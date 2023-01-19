cmake_minimum_required(VERSION 3.23)
project(my_cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

include_directories(.)
include_directories(sources)
include_directories(sources/tools)
include_directories(sources/utils)

add_executable(my_cpp
        main.cpp
        sources/utils/string_util.hpp
        sources/utils/registry_util.hpp
        sources/utils/registry_util.hpp
        sources/tools/HTTPRequest.hpp)

set(GOOGLETEST_VERSION 1.12.1)
add_subdirectory(external/googletest)
include_directories(external/googletest/include)
target_link_libraries(my_cpp gtest_main)


add_subdirectory(external/spdlog1x)
include_directories(external/spdlog1x/include)