cmake_minimum_required(VERSION 3.22)
project(PhysicsPoC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

include_directories(${PROJECT_SOURCE_DIR}/includes)

add_executable(PhysicsPoC
        src/main.cpp
        src/PhysicsObject.cpp
)

target_link_libraries(PhysicsPoC PRIVATE SDL3::SDL3)
