cmake_minimum_required(VERSION 3.7)
project(HRAg2_update)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c cmake-build-debug/variables.h)
add_executable(HRAg2_update ${SOURCE_FILES})