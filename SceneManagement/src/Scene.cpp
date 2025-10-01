//
// Created by jusra on 1-10-2025.
//

#include "../includes/Scene.h"

void Scene::openScene(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    this->render(renderer);
}

void Scene::drawRectangle(SDL_Renderer *renderer, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    SDL_FRect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 500;
    rect.h = 500;

    SDL_RenderFillRect(renderer, &rect);
}

std::string Scene::getName() {
    return name;
}
