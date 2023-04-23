cmake_minimum_required(VERSION 3.16)
project(ex2_os)

set(CMAKE_CXX_STANDARD 14)

include_directories(resources)

add_executable(ex2_os
        resources/main.cpp
        resources/uthreads.cpp
        resources/uthreads.h)
