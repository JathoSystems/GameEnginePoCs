cmake_minimum_required(VERSION 3.22)
project(AudioPoC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(AudioPoC
        src/main.cpp
)

target_link_libraries(AudioPoC PRIVATE SDL3::SDL3)