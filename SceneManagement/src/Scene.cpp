//
// Created by jusra on 1-10-2025.
//

#include "../includes/Scene.h"

void Scene::openScene(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    this->render(renderer);
}

std::string Scene::getName() {
    return name;
}
