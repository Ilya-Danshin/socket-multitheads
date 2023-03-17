cmake_minimum_required(VERSION 3.22)
project(Program1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Program1 main.cpp
        Program1/IProgram1.h Program1/Program1.h Program1/Program1.cpp
        Program1/Thread/IThread.h
        Program1/Thread/Thread1/Thread1.h Program1/Thread/Thread1/Thread1.cpp
        Program1/Thread/Thread2/Thread2.h Program1/Thread/Thread2/Thread2.cpp)

find_package(Threads REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} Threads::Threads)
