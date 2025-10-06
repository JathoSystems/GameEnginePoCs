cmake_minimum_required(VERSION 3.16)
project(UIElement VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SDLTTF_VENDORED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(libraries/SDL EXCLUDE_FROM_ALL)
add_subdirectory(libraries/SDL_TTF EXCLUDE_FROM_ALL)
add_subdirectory(libraries/SDL_image EXCLUDE_FROM_ALL)

add_executable(UIElement
        src/main.cpp
        src/Utils/Size.cpp
        include/Utils/Size.h
        src/Components/Window.cpp
        include/Components/Window.h
        src/Utils/Position.cpp
        include/Utils/Position.h
        src/Utils/Scale.cpp
        include/Utils/Scale.h
        src/Components/Rectangle.cpp
        include/Components/Rectangle.h
        src/Utils/Color.cpp
        include/Utils/Color.h
        src/Components/Text.cpp
        include/Components/Text.h
        include/Components/UIElement.h
        src/Components/UIElement.cpp
        include/Components/Sprite.h
        src/Components/Sprite.cpp
        include/UIElementManager.h
        src/UIElementManager.cpp
        src/Animation/Animation.cpp
        include/Animation/Animation.h
        src/Animation/Keyframe.cpp
        include/Animation/Keyframe.h
        include/Animation/AnimationType.h
)

target_compile_definitions(UIElement PRIVATE
        ASSET_PATH="${CMAKE_SOURCE_DIR}/assets"
)

target_link_libraries(UIElement PRIVATE SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3::SDL3)
