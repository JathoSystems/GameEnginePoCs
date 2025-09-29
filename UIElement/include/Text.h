//
// Created by jusra on 29-9-2025.
//

#ifndef UIELEMENT_TEXT_H
#define UIELEMENT_TEXT_H
#include <string>

#include "Color.h"
#include "SDL3/SDL_render.h"

class Text {
private:
    Color* _color;
    std::string _text;
public:
    Text(Color* color, std::string text);
    void render(SDL_Renderer* renderer);
};

#endif //UIELEMENT_TEXT_H