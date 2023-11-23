cmake_minimum_required(VERSION 3.24)
project(MB_TOg_Programming_Language)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(MB_TOg_Programming_Language
        src/Executor.cpp
        src/Lexer.cpp
        src/Parser.cpp
         main.cpp)
