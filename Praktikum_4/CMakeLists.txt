cmake_minimum_required(VERSION 2.6)

project(Praktikum_4)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++1z)

configure_file(${PROJECT_SOURCE_DIR}/graph1.txt ${PROJECT_BINARY_DIR}/graph1.txt COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/graph2.txt ${PROJECT_BINARY_DIR}/graph2.txt COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/graph3.txt ${PROJECT_BINARY_DIR}/graph3.txt COPYONLY)


add_executable(Praktikum4 P4_main.cpp P4_graph.cpp P4_graphnode.cpp)
