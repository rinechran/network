# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.7)

project ("network packet")

set(CMAKE_CXX_STANDARD 20)



include_directories(includes)
include_directories (libraries/fmt/include)
include_directories(libraries/doctest/doctest)

# Include sub-projects
add_subdirectory (libraries/fmt)


# Excute project
add_subdirectory (src)


