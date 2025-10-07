//
// Created by jusra on 1-10-2025.
//

#include "../../includes/Scenes/HouseScene.h"

#include <SDL3/SDL.h>

void HouseScene::render(SDL_Renderer *renderer, int camX, int camY) {
    // Sky gradient (achtergrond)
    this->drawRectangle(renderer, 135, 206, 235, 0, 0, 1000, 1000, camX, camY);

    // === RETRO HUT ===
    // Hut muren (bruin)
    this->drawRectangle(renderer, 139, 90, 43, 200, 300, 200, 150, camX, camY);

    // Dak (donkerrood)
    this->drawRectangle(renderer, 178, 34, 34, 180, 250, 60, 50, camX, camY);
    this->drawRectangle(renderer, 178, 34, 34, 240, 250, 60, 50, camX, camY);
    this->drawRectangle(renderer, 178, 34, 34, 300, 250, 60, 50, camX, camY);
    this->drawRectangle(renderer, 178, 34, 34, 360, 250, 60, 50, camX, camY);

    // Deur (donkerbruin)
    this->drawRectangle(renderer, 101, 67, 33, 270, 380, 60, 70, camX, camY);

    // Raam (lichtblauw)
    this->drawRectangle(renderer, 173, 216, 230, 220, 330, 40, 40, camX, camY);
    this->drawRectangle(renderer, 173, 216, 230, 340, 330, 40, 40, camX, camY);

    // === BOOM (links) ===
    // Stam (bruin)
    this->drawRectangle(renderer, 101, 67, 33, 80, 350, 30, 100, camX, camY);

    // Bladeren (groen)
    this->drawRectangle(renderer, 34, 139, 34, 50, 300, 30, 30, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 80, 300, 30, 30, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 110, 300, 30, 30, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 65, 270, 30, 30, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 95, 270, 30, 30, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 80, 240, 30, 30, camX, camY);

    // === GRAS (grond) ===
    this->drawRectangle(renderer, 34, 139, 34, 0, 450, 1000, 50, camX, camY);

    // === ZON ===
    this->drawRectangle(renderer, 255, 255, 0, 450, 50, 40, 40, camX, camY);

    // === WOLKEN ===
    this->drawRectangle(renderer, 255, 255, 255, 350, 80, 30, 20, camX, camY);
    this->drawRectangle(renderer, 255, 255, 255, 380, 80, 30, 20, camX, camY);
    this->drawRectangle(renderer, 255, 255, 255, 365, 65, 30, 20, camX, camY);

    this->drawRectangle(renderer, 255, 255, 255, 150, 100, 30, 20, camX, camY);
    this->drawRectangle(renderer, 255, 255, 255, 180, 100, 30, 20, camX, camY);
    this->drawRectangle(renderer, 255, 255, 255, 165, 85, 30, 20, camX, camY);

    // === BLOEMEN ===
    // Rode bloemen
    this->drawRectangle(renderer, 255, 0, 0, 440, 430, 15, 15, camX, camY);
    this->drawRectangle(renderer, 255, 0, 0, 480, 425, 15, 15, camX, camY);

    // Gele bloemen
    this->drawRectangle(renderer, 255, 255, 0, 150, 435, 15, 15, camX, camY);
    this->drawRectangle(renderer, 255, 255, 0, 180, 430, 15, 15, camX, camY);

    // === PAD (naar huis) ===
    this->drawRectangle(renderer, 210, 180, 140, 270, 450, 60, 50, camX, camY);
    this->drawRectangle(renderer, 210, 180, 140, 285, 500, 30, 100, camX, camY);
}