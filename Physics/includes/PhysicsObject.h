#pragma once

#include <SDL3/SDL.h>

class PhysicsObject {
public:
    PhysicsObject(float x, float y, float width, float height);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    void reset();

private:
    float x, y;
    float velocityY;
    float width, height;
    const float gravity = 9.81f;
};
