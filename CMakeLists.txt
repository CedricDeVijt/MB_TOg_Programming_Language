cmake_minimum_required(VERSION 3.22.1)
project(MB_TOg_Programming_Language)

set(CMAKE_CXX_STANDARD 17)

set(
        MODULES
        src/modules/Executor.cpp
        src/modules/Lexer.cpp
        src/modules/Parser.cpp
)

set(
        EXCEPTIONS
        src/exceptions/FileNotFoundError.h
        src/exceptions/ArgsError.h
)

set(
        DATATYPES
        src/datatypes/CFG.cpp
        src/datatypes/Token.cpp
        src/datatypes/AST.cpp
)

set(
        SRC
        ${MODULES}
        ${CONNECTORS}
        ${DATATYPES}
        src/MyLang.cpp
        src/modules/executionEnvironment/Environment.cpp
)

add_executable(myLang ${SRC} main.cpp)