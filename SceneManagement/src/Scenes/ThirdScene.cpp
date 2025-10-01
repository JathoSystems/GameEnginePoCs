//
// Created by jusra on 1-10-2025.
//

#include "../../includes/Scenes/ThirdScene.h"

#include <SDL3/SDL.h>

void ThirdScene::render(SDL_Renderer* renderer) {
    this->drawRectangle(renderer, 0, 0, 255);
}
