//
// Created by jusra on 29-9-2025.
//

#include "../../include/Utils/Color.h"
#include "../../include/Utils/Position.h"
#include "../../include/Utils/Size.h"
#include "../../include/Components/Window.h"

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_video.h"

void Window::open(std::string title) {
    SDL_Init(SDL_INIT_VIDEO);

    _window = SDL_CreateWindow(
        title.c_str(),
        _size->getWidth(),
        _size->getHeight(),
        SDL_WINDOW_OPENGL
    );

    if (!_window) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    }
}

void Window::close() {
    SDL_DestroyWindow(_window);
    SDL_Quit();
}


SDL_Window * Window::getSdlWindow() {
    return _window;
}

void Window::setSize(int width, int height) {
    if (!_size) _size = new Size(width, height);
    else {
        _size->setWidth(width);
        _size->setHeight(height);
    }
}

Size* Window::getSize() {
    return _size;
}

void Window::setColor(int r, int g, int b) {
    if (!_color) _color = new Color(r, g, b);
    else {
        _color->setR(r);
        _color->setG(g);
        _color->setB(b);
    }
}

Color * Window::getColor() {
    return _color;
}
