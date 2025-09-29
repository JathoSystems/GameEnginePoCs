//
// Created by jusra on 29-9-2025.
//

#ifndef UIELEMENT_RECTANGLE_H
#define UIELEMENT_RECTANGLE_H
#include "Color.h"
#include "Position.h"
#include "Scale.h"
#include "Size.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"


class Rectangle {
private:
    Position* _position;
    Scale* _scale;
    Size* _size;
public:
    Rectangle(Position* position, Size* size, Scale* scale);
    void draw(SDL_Renderer* renderer, Color* color);
};


#endif //UIELEMENT_RECTANGLE_H