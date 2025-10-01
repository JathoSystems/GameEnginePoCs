//
// Created by jusra on 1-10-2025.
//

#include "../../includes/Scenes/FirstScene.h"

#include <SDL3/SDL.h>

void FirstScene::render(SDL_Renderer* renderer) {
    this->drawRectangle(renderer, 255, 0, 0);
}
