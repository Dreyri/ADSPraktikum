cmake_minimum_required (VERSION 2.6)
project(Praktikum_23)

SET(CLANG_CXX11_SUPPORT "-std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX11_SUPPORT}")

add_executable(Praktikum_23 main.cpp tree.cpp treenode.cpp Ringpuffer.cpp RingNode.cpp)
