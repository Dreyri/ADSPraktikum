cmake_minimum_required(VERSION 2.6)

project(Praktikum_5)

find_package(X11)

include_directories(${X11_INCLUDE_DIRS})
include_directories(/opt/local/include/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wno-narrowing")

configure_file(${PROJECT_SOURCE_DIR}/Campus_Eupener_Strasse.bmp ${PROJECT_BINARY_DIR}/Campus_Eupener_Strasse.bmp COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/Test2.bmp ${PROJECT_BINARY_DIR}/Test2.bmp COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/hist.bmp ${PROJECT_BINARY_DIR}/hist.bmp COPYONLY)


add_executable(Praktikum5 main.cpp CImg.h IOSystem.h Huffman_IO.h)
target_link_libraries(Praktikum5 ${X11_LIBRARIES})
