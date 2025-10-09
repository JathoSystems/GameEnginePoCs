cmake_minimum_required(VERSION 3.22)
project(PhysicsPoC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --- SDL3 ---
FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

# --- Box2D ---
FetchContent_Declare(
        Box2D
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1
)

# Disable extras that cause your errors/warnings
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "Disable Box2D unit tests" FORCE)
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "Disable Box2D testbed app" FORCE)
set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "Disable Box2D examples" FORCE)

FetchContent_MakeAvailable(Box2D)

include_directories(${PROJECT_SOURCE_DIR}/includes)

add_executable(PhysicsPoC
        src/main.cpp
        src/Physics.cpp
        src/PhysicsObject.cpp
)

target_link_libraries(PhysicsPoC PRIVATE SDL3::SDL3 box2d)
