cmake_minimum_required(VERSION 3.22)
project(Program2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Program2 main.cpp
        Program2/IProgram2.h Program2/Program2.h Program2/Program2.cpp)
