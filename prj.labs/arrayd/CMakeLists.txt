cmake_minimum_required(VERSION 3.20)
project(rational_library)

set(CMAKE_CXX_STANDARD 23)

add_library(arrayd arrayd.cpp arrayd.hpp)

target_include_directories(arrayd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})