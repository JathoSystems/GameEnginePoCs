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
    void drawRectangle(SDL_Renderer* renderer, int r, int g, int b);
    std::string getName();

    virtual void render(SDL_Renderer* renderer) = 0;
};

#endif //UIELEMENT_SCENE_H