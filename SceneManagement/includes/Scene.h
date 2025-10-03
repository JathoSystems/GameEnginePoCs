//
// Created by jusra on 1-10-2025.
//

#ifndef UIELEMENT_SCENE_H
#define UIELEMENT_SCENE_H

#include <memory>
#include <string>
#include <SDL3/SDL.h>

class Scene {
private:
    std::string name;

public:
    Scene(std::string name) : name(name) {}
    virtual ~Scene() = default;

    void openScene(SDL_Renderer *renderer);
    std::string getName();

    virtual void render(SDL_Renderer* renderer, int camX = 0, int camY = 0) = 0;

    void drawRectangle(SDL_Renderer* renderer, int r, int g, int b, int x, int y, int width, int height, int camX = 0, int camY = 0) {
        SDL_FRect rect;  // Changed to SDL_FRect for SDL3
        rect.x = x - camX; // offset van camera aftrekken
        rect.y = y - camY;
        rect.w = width;
        rect.h = height;
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &rect);  // Already using pointer with &
    }
};

#endif //UIELEMENT_SCENE_H