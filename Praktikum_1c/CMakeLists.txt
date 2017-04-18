cmake_minimum_required (VERSION 2.6)
project (ADSPraktikum1c)

SET(CLANG_CXX11_SUPPORT "-std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX11_SUPPORT}")
add_executable(Praktikum_1c main.cpp node.h list.h tweet.h)
