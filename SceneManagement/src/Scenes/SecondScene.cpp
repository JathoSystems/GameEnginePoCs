//
// Created by jusra on 1-10-2025.
//

#include "../../includes/Scenes/SecondScene.h"

#include <SDL3/SDL.h>

void SecondScene::render(SDL_Renderer* renderer) {
    this->drawRectangle(renderer, 0, 255, 0);
}
