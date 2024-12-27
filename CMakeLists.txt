cmake_minimum_required(VERSION 3.16)
project(MapListTest)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 添加源文件
add_executable(MapListTest
        src/Headers/maplist.hpp
        src/Headers/error.cpp
        src/Headers/test.cpp
)

# 设置包含路径
target_include_directories(MapListTest PRIVATE ${CMAKE_SOURCE_DIR}/Headers)