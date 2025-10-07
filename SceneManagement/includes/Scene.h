//
// Created by jusra on 1-10-2025.
//

#ifndef UIELEMENT_SCENE_H
#define UIELEMENT_SCENE_H

#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <SDL3/SDL.h>

#include "Element/Button.h"

class Scene {
private:
    std::string name;
    std::vector<Button> buttons;

public:
    Scene(std::string name) : name(name) {
    }

    virtual ~Scene() = default;

    void openScene(SDL_Renderer *renderer);

    std::string getName();

    virtual void render(SDL_Renderer *renderer, int camX = 0, int camY = 0) = 0;

    void drawRectangle(SDL_Renderer *renderer, int r, int g, int b, int x, int y, int width, int height, int camX = 0,
                       int camY = 0);

    void addButton(int x, int y, int width, int height,
                   std::function<void()> onClick,
                   SDL_Color bgColor = {100, 100, 100, 255});

    void renderButtons(SDL_Renderer *renderer);

    void handleMouseMove(int mouseX, int mouseY);

    void handleMouseClick(int mouseX, int mouseY);

    void clearButtons();
};

#endif //UIELEMENT_SCENE_H
