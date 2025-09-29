//
// Created by jusra on 29-9-2025.
//

#ifndef UIELEMENT_WINDOW_H
#define UIELEMENT_WINDOW_H
#include <string>

#include <SDL3/SDL.h>

class Window {
private:
    SDL_Window *window;

public:
    void open(std::string title);

    void close();

    SDL_Window* getSdlWindow();
};


#endif //UIELEMENT_WINDOW_H