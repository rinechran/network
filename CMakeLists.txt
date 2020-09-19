# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.7)


set(CMAKE_CXX_STANDARD 17)

project ("network packet")


# Include 
include_directories (includes)
include_directories(libraries/doctest/doctest)
include_directories(libraries/fmt/include)


add_subdirectory(libraries/fmt)

# Include sub-projects
add_subdirectory (src)
