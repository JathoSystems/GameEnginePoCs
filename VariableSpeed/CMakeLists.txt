cmake_minimum_required(VERSION 3.16)
project(VariableSpeed VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(SDLTTF_VENDORED ON)

add_subdirectory(libraries/SDL EXCLUDE_FROM_ALL)

add_executable(VariableSpeed
        src/main.cpp
)

target_link_libraries(VariableSpeed PRIVATE SDL3::SDL3)
