cmake_minimum_required(VERSION 3.16)
project(MapListTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(MapListTest
        src/Headers/error.cpp
        src/Headers/BookManager.hpp
        src/Headers/test.cpp
)