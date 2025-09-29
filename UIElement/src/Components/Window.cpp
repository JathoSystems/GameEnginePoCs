//
// Created by jusra on 29-9-2025.
//

#include "../../include/Window.h"

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_video.h"

void Window::open(std::string title) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        title.c_str(),
        640, 480,
        SDL_WINDOW_OPENGL
    );

    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    }
}

void Window::close() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}


SDL_Window * Window::getSdlWindow() {
    return window;
}
