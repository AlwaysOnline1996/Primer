cmake_minimum_required(VERSION 3.8)
project(C__Primer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp String/String.cpp String/String.h)
add_executable(C__Primer ${SOURCE_FILES})