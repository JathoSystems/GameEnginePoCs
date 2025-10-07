//
// Created by jusra on 1-10-2025.
//

#include "../includes/Scene.h"

void Scene::openScene(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    this->render(renderer);
}

std::string Scene::getName() {
    return name;
}

void Scene::drawRectangle(SDL_Renderer *renderer, int r, int g, int b, int x, int y, int width, int height, int camX,
                          int camY) {
    SDL_FRect rect;
    rect.x = x - camX;
    rect.y = y - camY;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Scene::addButton(int x, int y, int width, int height, std::function<void()> onClick, SDL_Color bgColor) {
    buttons.emplace_back(x, y, width, height, onClick, bgColor);
}

void Scene::renderButtons(SDL_Renderer *renderer) {
    for (const auto &button: buttons) {
        SDL_Color color = button.isHovered()
                              ? SDL_Color{
                                  static_cast<Uint8>(button.getBackgroundColor().r + 30),
                                  static_cast<Uint8>(button.getBackgroundColor().g + 30),
                                  static_cast<Uint8>(button.getBackgroundColor().b + 30), 255
                              }
                              : button.getBackgroundColor();

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_FRect rect = {
            static_cast<float>(button.getX()), static_cast<float>(button.getY()),
            static_cast<float>(button.getWidth()), static_cast<float>(button.getHeight())
        };
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderRect(renderer, &rect);
    }
}

void Scene::handleMouseMove(int mouseX, int mouseY) {
    for (auto &button: buttons) {
        button.setHovered(button.contains(mouseX, mouseY));
    }
}

void Scene::handleMouseClick(int mouseX, int mouseY) {
    for (Button &button: buttons) {
        if (button.contains(mouseX, mouseY)) {
            button.click();
        }
    }
}

void Scene::clearButtons() {
    buttons.clear();
}
