cmake_minimum_required(VERSION 3.16)
project(SceneManagement VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SDLTTF_VENDORED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(libraries/SDL EXCLUDE_FROM_ALL)

add_executable(SceneManagement
        src/main.cpp
        includes/Scenes/FirstScene.h
        src/Scenes/FirstScene.cpp
        src/Scene.cpp
        src/SceneManager.cpp
        includes/Camera/Camera.h
)

target_link_libraries(SceneManagement PRIVATE SDL3::SDL3)
