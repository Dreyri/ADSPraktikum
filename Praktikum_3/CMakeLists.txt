cmake_minimum_required (VERSION 2.6)
project(Praktikum_3)


if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "Configuring for Mac OSX")
    set(CMAKE_CXX_COMPILER g++)
    #set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fopenmp)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++1z)
    INCLUDE_DIRECTORIES(/opt/local/include/libomp)
    LINK_DIRECTORIES(/opt/local/lib/libomp)
endif()

add_executable(Praktikum3 main.cpp MyAlgorithms.cpp)
target_link_libraries(Praktikum3 omp)
