﻿project (Network_Packet)

set(CMAKE_CXX_FLAGS -pthread)
cmake_minimum_required(VERSION 3.8)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../includes
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries
)

file(GLOB_RECURSE SOURCE "*.cpp" "*.hpp")

add_executable (${PROJECT_NAME} ${SOURCE} )


target_link_libraries(${PROJECT_NAME}
    fmt::fmt
)
