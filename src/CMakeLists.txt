project (Network_Packet)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../Includes
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries
)

file(GLOB_RECURSE SOURCE "*.cpp")

add_executable (${PROJECT_NAME} ${SOURCE})


target_link_libraries(${PROJECT_NAME}
    fmt::fmt
)
