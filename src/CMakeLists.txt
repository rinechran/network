# CMakeList.txt : CMake project for network packet, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# Includes
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../includes
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries
)


# Add source to this project's executable.
add_executable (CMakeTarget "main.cpp")

# TODO: Add tests and install targets if needed.
