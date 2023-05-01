#cmake_minimum_required(VERSION 3.16)
#project(ex2_os)
#
#set(CMAKE_CXX_STANDARD 14)
#
#include_directories(resources)
#
#add_executable(ex2_os
#        resources/main.cpp
#        resources/uthreads.cpp
#        resources/uthreads.h)
cmake_minimum_required(VERSION 3.1)
#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
project(threads VERSION 1.0 LANGUAGES C CXX)

add_library(uthreads resources/uthreads.h resources/uthreads.cpp)

set_property(TARGET uthreads PROPERTY CXX_STANDARD 11)
target_compile_options(uthreads PUBLIC -Wall -Wextra)

add_subdirectory(tests)