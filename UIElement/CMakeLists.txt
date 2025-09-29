cmake_minimum_required(VERSION 3.16)
project(UIElement VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SDLTTF_VENDORED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(libraries/SDL EXCLUDE_FROM_ALL)
add_subdirectory(libraries/SDL_TTF EXCLUDE_FROM_ALL)

add_executable(UIElement
        src/main.cpp
        src/Utils/Size.cpp
        include/Size.h
        src/Components/Window.cpp
        include/Window.h
        src/Utils/Position.cpp
        include/Position.h
        src/Utils/Scale.cpp
        include/Scale.h
        src/Components/Rectangle.cpp
        include/Rectangle.h
        src/Utils/Color.cpp
        include/Color.h
        src/Components/Text.cpp
        include/Text.h
        src/Components/Text.cpp
)

target_link_libraries(UIElement PRIVATE SDL3_ttf::SDL3_ttf SDL3::SDL3)
