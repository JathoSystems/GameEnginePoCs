//
// Created by jusra on 29-9-2025.
//

#ifndef UIELEMENT_RECTANGLE_H
#define UIELEMENT_RECTANGLE_H

#include "UIElement.h"
#include "../../include/Utils/Color.h"
#include "SDL3/SDL_render.h"

class Rectangle : public UIElement {
private:
    SDL_Texture *_texture;
public:

    void render(SDL_Renderer* renderer) override;
};


#endif //UIELEMENT_RECTANGLE_H