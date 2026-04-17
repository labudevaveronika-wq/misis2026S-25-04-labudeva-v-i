cmake_minimum_required(VERSION 3.10)
project(misis_labs)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/prj.thirdparty")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(BitsetD)
add_subdirectory(complex)
add_subdirectory(rational)
add_subdirectory(arrayd)
add_subdirectory(stacka)
add_subdirectory(stackl)
