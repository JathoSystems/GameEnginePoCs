cmake_minimum_required(VERSION 3.16)
project(SceneManagement VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(SDLTTF_VENDORED ON)

add_subdirectory(libraries/SDL EXCLUDE_FROM_ALL)
add_subdirectory(libraries/SDL_TTF EXCLUDE_FROM_ALL)

add_executable(FPSCounter
        src/main.cpp
        src/FPSCounter.cpp
        includes/FPSCounter.h
)

target_link_libraries(FPSCounter PRIVATE SDL3_ttf::SDL3_ttf SDL3::SDL3)
