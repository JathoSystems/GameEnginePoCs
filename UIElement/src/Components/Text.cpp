#include "../../include/Components/Text.h"
#include "../../include/Utils/Color.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

Text::Text(std::string text) {
    this->_text = text;
}

void Text::render(SDL_Renderer* renderer) {
    if (!renderer) return;

    // Open font (één keer kan beter)
    static TTF_Font* font = TTF_OpenFont("../../assets/fonts/TestFont.ttf", this->_fontSize * _scale->getScale());
    if (!font) {
        SDL_Log("Failed to open font: %s", SDL_GetError());
        return;
    }

    SDL_Color sdlColor = { static_cast<Uint8>(_color->getR()),
                           static_cast<Uint8>(_color->getG()),
                           static_cast<Uint8>(_color->getB()),
                           255 };

    // Render text naar surface (Solid)
    SDL_Surface* surface = TTF_RenderText_Solid(font, _text.c_str(), 0, sdlColor);
    if (!surface) {
        SDL_Log("Failed to render text: %s", SDL_GetError());
        return;
    }

    // Zet surface om naar texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    int w = surface->w;
    int h = surface->h;
    SDL_DestroySurface(surface);

    if (!texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        return;
    }

    SDL_FRect dstRect = {static_cast<float>(_position->getX()), static_cast<float>(_position->getY()), static_cast<float>(w), static_cast<float>(h)};
    SDL_RenderTexture(renderer, texture, nullptr, &dstRect);

    SDL_DestroyTexture(texture);
}

int Text::getFontSize() {
    return _fontSize;
}

std::string Text::getText() {
    return _text;
}

void Text::setText(std::string text) {
    this->_text = text;
}

void Text::setFontSize(int fontSize) {
    this->_fontSize = fontSize;
}
