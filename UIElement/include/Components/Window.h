//
// Created by jusra on 29-9-2025.
//

#ifndef UIELEMENT_WINDOW_H
#define UIELEMENT_WINDOW_H
#include <string>
#include "../Utils/Size.h"
#include "../Utils/Color.h"

#include <SDL3/SDL.h>

class Window {
private:
    SDL_Window *_window;
    Size *_size;
    Color *_color;

public:
    void open(std::string title);

    void close();

    SDL_Window *getSdlWindow();

    void setSize(int width, int height);

    Size *getSize();

    void setColor(int r, int g, int b);

    Color *getColor();
};


#endif //UIELEMENT_WINDOW_H
