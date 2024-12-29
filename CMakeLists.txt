cmake_minimum_required(VERSION 3.16)
project(MapListTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(code
        src/Headers/error.cpp
        src/Headers/BookManager.cpp
        src/Headers/LogManager.cpp
        src/Headers/tokenscanner.cpp
        src/Headers/AccountManager.cpp
        src/main.cpp
)