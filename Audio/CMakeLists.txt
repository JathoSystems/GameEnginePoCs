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

FetchContent_Declare(
        SDL3_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL3_mixer)

add_executable(AudioPoC
        src/main.cpp
        src/AudioMixer.cpp
)
target_include_directories(AudioPoC PRIVATE ${PROJECT_SOURCE_DIR}/includes)
target_link_libraries(AudioPoC PRIVATE SDL3::SDL3 SDL3_mixer::SDL3_mixer)
