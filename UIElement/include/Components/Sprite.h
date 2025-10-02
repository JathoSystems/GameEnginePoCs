//
// Created by jusra on 30-9-2025.
//

#ifndef UIELEMENT_SPRITE_H
#define UIELEMENT_SPRITE_H
#include <string>
#include <SDL3/SDL.h>
#include "UIElement.h"

class Sprite : public UIElement {
private:
    std::string _imagePath;
    SDL_Texture* _texture;
    int _frameWidth;
    int _frameHeight;
    int _currentFrame;
    int _totalFrames;
    float _animationSpeed;
    float _timeAccumulator;

public:
    Sprite(std::string imagePath);
    virtual ~Sprite();

    bool loadTexture(SDL_Renderer* renderer, int frameWidth = 0, int frameHeight = 0, int totalFrames = 1);
    void render(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;

    void setAnimationSpeed(float speed) { _animationSpeed = speed; }
    void setTotalFrames(int frames) { _totalFrames = frames; }
};

#endif //UIELEMENT_SPRITE_H