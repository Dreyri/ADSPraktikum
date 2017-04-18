cmake_minimum_required (VERSION 2.6)
project(Praktikum_2)

SET(CLANG_CXX11_SUPPORT "-std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX11_SUPPORT}")

add_executable(Praktikum_2 main.cpp Ringpuffer.cpp RingNode.cpp)
