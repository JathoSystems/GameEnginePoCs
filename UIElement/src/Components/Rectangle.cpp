//
// Created by jusra on 29-9-2025.
//

#include "../../include/Rectangle.h"

#include <SDL3/SDL.h>

#include "../../include/Color.h"

class Color;

Rectangle::Rectangle(Position *position, Size* size, Scale *scale) {
    this->_position = position;
    this->_scale = scale;
    this->_size = size;
}

void Rectangle::draw(SDL_Renderer* renderer, Color* color) {
    if (!renderer) {
        SDL_Log("Renderer kon niet aangemaakt worden: %s", SDL_GetError());
        return;
    }

    // Stel kleur in (rood, groen, blauw, alpha)
    SDL_SetRenderDrawColor(renderer, color->getR(), color->getG(), color->getB(), 255);

    SDL_FRect rect{
        static_cast<float>(_position->getX()),
        static_cast<float>(_position->getY()),
        (float) _scale->getScale() * _size->getWidth(),
        (float) _scale->getScale() * _size->getHeight()
    };

    // Teken gevulde rechthoek
    SDL_RenderFillRect(renderer, &rect);

    // Alles tonen
    SDL_RenderPresent(renderer);

    SDL_DestroyRenderer(renderer);
}