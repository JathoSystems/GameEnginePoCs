#include "../../include/Components/Text.h"
#include "../../include/Utils/Color.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

Text::Text(std::string text) {
    this->_text = text;
}

Text::~Text() {
    if (_font) {
        // TTF_CloseFont(_font);
        _font = nullptr;
    }
}

void Text::render(SDL_Renderer* renderer) {
    if (!renderer) return;

    if (!_font) {
        std::string fontPath = std::string(ASSET_PATH) + "/fonts/TestFont.ttf";
        _font = TTF_OpenFont(fontPath.c_str(), static_cast<float>(_fontSize * _scale->getScale()));
        if (!_font) {
            SDL_Log("Failed to open font: %s", SDL_GetError());
            return;
        }
    }

    SDL_Color sdlColor = { static_cast<Uint8>(_color->getR()),
                           static_cast<Uint8>(_color->getG()),
                           static_cast<Uint8>(_color->getB()),
                           255 };

    // SDL_Surface* surface = TTF_RenderText_Solid(_font, _text.c_str(), 0, sdlColor);
    SDL_Surface* surface = TTF_RenderText_Solid(_font, _text.c_str(), 0, sdlColor);
    if (!surface) {
        SDL_Log("Failed to render text: %s", SDL_GetError());
        return;
    }

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
