//
// Created by jusra on 30-9-2025.
//

#include "../../include/Components/Sprite.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Sprite::Sprite(std::string imagePath)
    : _imagePath(imagePath), _texture(nullptr), _frameWidth(0), _frameHeight(0),
      _currentFrame(0), _totalFrames(1), _animationSpeed(0), _timeAccumulator(0.0f) {
}

Sprite::~Sprite() {
    if (_texture) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }
}

bool Sprite::loadTexture(SDL_Renderer* renderer, int frameWidth, int frameHeight, int totalFrames) {
    if (_imagePath.empty()) {
        SDL_Log("Image path is empty, cannot load texture.");
        return false;
    }

    SDL_Surface* surface = IMG_Load(_imagePath.c_str());
    if (!surface) {
        SDL_Log("Failed to load image '%s': %s", _imagePath.c_str(), SDL_GetError());
        return false;
    }

    _texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!_texture) {
        SDL_Log("Failed to create texture from '%s': %s", _imagePath.c_str(), SDL_GetError());
        SDL_DestroySurface(surface);
        return false;
    }

    int texWidth = surface->w;
    int texHeight = surface->h;
    SDL_DestroySurface(surface);

    _totalFrames = (totalFrames > 0) ? totalFrames : 1;

    // Als geen frame grootte is opgegeven, bereken automatisch
    if (frameWidth == 0) _frameWidth = texWidth / _totalFrames;
    else _frameWidth = frameWidth;

    if (frameHeight == 0) _frameHeight = texHeight;
    else _frameHeight = frameHeight;

    // Als de UIElement size nog niet gezet is, gebruik frame size als default
    if (_size->getWidth() == 0) _size->setWidth(_frameWidth);
    if (_size->getHeight() == 0) _size->setHeight(_frameHeight);

    return true;
}

void Sprite::update(float deltaTime) {
    if (_totalFrames <= 1 || _animationSpeed <= 0.0f) return;

    _timeAccumulator += deltaTime;
    float frameTime = 1.0f / _animationSpeed;

    while (_timeAccumulator >= frameTime) {
        _currentFrame = (_currentFrame + 1) % _totalFrames;
        _timeAccumulator -= frameTime;
    }
}

void Sprite::render(SDL_Renderer* renderer) {
    if (!_texture) {
        SDL_Log("Texture not loaded!");
        return;
    }

    SDL_FRect srcRect;
    srcRect.x = _currentFrame * _frameWidth;
    srcRect.y = 0;
    srcRect.w = _frameWidth;
    srcRect.h = _frameHeight;

    SDL_FRect destRect;
    destRect.x = _position->getX();
    destRect.y = _position->getY();
    destRect.w = static_cast<float>(_size->getWidth() * _scale->getScale());
    destRect.h = static_cast<float>(_size->getHeight() * _scale->getScale());

    SDL_RenderTexture(renderer, _texture, &srcRect, &destRect);
}