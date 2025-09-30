//
// Created by jusra on 29-9-2025.
//

#include "../../include/Components/Rectangle.h"

#include <SDL3/SDL.h>

#include "../../include/Utils/Color.h"
#include "../../include/Utils/Position.h"
#include "../../include/Utils/Size.h"
#include "../../include/Utils/Scale.h"

void Rectangle::render(SDL_Renderer *renderer) {
    if (!renderer) {
        SDL_Log("Renderer kon niet aangemaakt worden: %s", SDL_GetError());
        return;
    }

    SDL_SetRenderDrawColor(renderer, _color->getR(), _color->getG(), _color->getB(), 255);

    SDL_FRect rect{
        static_cast<float>(_position->getX()),
        static_cast<float>(_position->getY()),
        (float) _scale->getScale() * _size->getWidth(),
        (float) _scale->getScale() * _size->getHeight()
    };

    SDL_RenderFillRect(renderer, &rect);
}
