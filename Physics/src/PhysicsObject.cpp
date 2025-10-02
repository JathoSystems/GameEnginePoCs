#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), velocityY(0) {}

void PhysicsObject::update(float deltaTime) {
    velocityY += gravity * deltaTime;
    y += velocityY * deltaTime;

    // Simple floor collision
    if (y + height > 600) {
        y = 600 - height;
        velocityY = 0;
    }
}

void PhysicsObject::render(SDL_Renderer* renderer) {
    SDL_FRect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void PhysicsObject::reset() {
    y = 100;
    velocityY = 0;
}

