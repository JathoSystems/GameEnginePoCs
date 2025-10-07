//
// Created by jusra on 7-10-2025.
//

#include "../../includes/Scenes/CityScene.h"

#include <iostream>
#include <ostream>
#include <SDL3/SDL.h>

void CityScene::render(SDL_Renderer *renderer, int camX, int camY) {
    // Lucht gradient (achtergrond - avondlucht)
    this->drawRectangle(renderer, 255, 140, 100, 0, 0, 1000, 300, camX, camY);
    this->drawRectangle(renderer, 100, 150, 200, 0, 300, 1000, 200, camX, camY);

    // === GEBOUW 1 (links - hoog) ===
    // Main building
    this->drawRectangle(renderer, 80, 80, 100, 50, 200, 120, 300, camX, camY);

    // Ramen (5 verdiepingen, 3 ramen breed)
    for (int floor = 0; floor < 5; floor++) {
        for (int window = 0; window < 3; window++) {
            this->drawRectangle(renderer, 255, 255, 150,
                70 + (window * 30), 230 + (floor * 50), 20, 30, camX, camY);
        }
    }

    // Dak
    this->drawRectangle(renderer, 60, 60, 80, 50, 180, 120, 20, camX, camY);

    // === GEBOUW 2 (midden - zeer hoog) ===
    // Main building
    this->drawRectangle(renderer, 90, 90, 110, 200, 150, 100, 350, camX, camY);

    // Ramen (7 verdiepingen, 2 ramen breed)
    for (int floor = 0; floor < 7; floor++) {
        for (int window = 0; window < 2; window++) {
            this->drawRectangle(renderer, 255, 255, 150,
                220 + (window * 35), 180 + (floor * 45), 25, 30, camX, camY);
        }
    }

    // Dak met antenne
    this->drawRectangle(renderer, 70, 70, 90, 200, 130, 100, 20, camX, camY);
    this->drawRectangle(renderer, 200, 50, 50, 245, 100, 10, 30, camX, camY);

    // === GEBOUW 3 (rechts - middelhoog) ===
    // Main building
    this->drawRectangle(renderer, 70, 90, 100, 330, 250, 140, 250, camX, camY);

    // Ramen (4 verdiepingen, 4 ramen breed)
    for (int floor = 0; floor < 4; floor++) {
        for (int window = 0; window < 4; window++) {
            this->drawRectangle(renderer, 255, 255, 150,
                345 + (window * 30), 280 + (floor * 50), 20, 30, camX, camY);
        }
    }

    // Dak
    this->drawRectangle(renderer, 50, 70, 80, 330, 230, 140, 20, camX, camY);

    // === GEBOUW 4 (achter - klein) ===
    this->drawRectangle(renderer, 100, 100, 120, 500, 280, 80, 220, camX, camY);

    // Ramen klein gebouw
    for (int floor = 0; floor < 3; floor++) {
        for (int window = 0; window < 2; window++) {
            this->drawRectangle(renderer, 255, 255, 150,
                515 + (window * 30), 310 + (floor * 50), 15, 25, camX, camY);
        }
    }

    // === WEG/STRAAT ===
    this->drawRectangle(renderer, 60, 60, 70, 0, 500, 1000, 100, camX, camY);

    // Straat markeringen (gele lijnen)
    for (int i = 0; i < 10; i++) {
        this->drawRectangle(renderer, 255, 255, 0,
            20 + (i * 100), 545, 60, 10, camX, camY);
    }

    // === STOEP ===
    this->drawRectangle(renderer, 120, 120, 120, 0, 450, 1000, 50, camX, camY);

    // === STRAATLANTAARNS ===
    // Lantaarn 1
    this->drawRectangle(renderer, 80, 80, 80, 150, 400, 10, 100, camX, camY);
    this->drawRectangle(renderer, 80, 80, 80, 135, 395, 40, 10, camX, camY);
    this->drawRectangle(renderer, 255, 200, 100, 140, 380, 30, 20, camX, camY);

    // Lantaarn 2
    this->drawRectangle(renderer, 80, 80, 80, 450, 400, 10, 100, camX, camY);
    this->drawRectangle(renderer, 80, 80, 80, 435, 395, 40, 10, camX, camY);
    this->drawRectangle(renderer, 255, 200, 100, 440, 380, 30, 20, camX, camY);

    // === BOMEN (op stoep) ===
    // Boom 1
    this->drawRectangle(renderer, 101, 67, 33, 240, 420, 15, 30, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 225, 400, 15, 15, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 240, 395, 15, 15, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 255, 400, 15, 15, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 240, 410, 15, 15, camX, camY);

    // Boom 2
    this->drawRectangle(renderer, 101, 67, 33, 380, 420, 15, 30, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 365, 400, 15, 15, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 380, 395, 15, 15, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 395, 400, 15, 15, camX, camY);
    this->drawRectangle(renderer, 34, 139, 34, 380, 410, 15, 15, camX, camY);

    // === MAAN ===
    this->drawRectangle(renderer, 240, 240, 255, 550, 60, 35, 35, camX, camY);

    // === STERREN ===
    this->drawRectangle(renderer, 255, 255, 255, 100, 80, 5, 5, camX, camY);
    this->drawRectangle(renderer, 255, 255, 255, 280, 50, 5, 5, camX, camY);
    this->drawRectangle(renderer, 255, 255, 255, 420, 90, 5, 5, camX, camY);
    this->drawRectangle(renderer, 255, 255, 255, 520, 120, 5, 5, camX, camY);
    this->drawRectangle(renderer, 255, 255, 255, 180, 110, 5, 5, camX, camY);
    this->drawRectangle(renderer, 255, 255, 255, 350, 70, 5, 5, camX, camY);

    // === VERKEERSBORDEN ===
    // Stop bord
    this->drawRectangle(renderer, 80, 80, 80, 300, 420, 8, 30, camX, camY);
    this->drawRectangle(renderer, 200, 0, 0, 290, 405, 28, 20, camX, camY);

    // === AUTO (geparkeerd) ===
    this->drawRectangle(renderer, 200, 50, 50, 100, 470, 70, 25, camX, camY);
    this->drawRectangle(renderer, 150, 40, 40, 115, 455, 40, 20, camX, camY);
    this->drawRectangle(renderer, 50, 50, 50, 105, 495, 15, 8, camX, camY);
    this->drawRectangle(renderer, 50, 50, 50, 150, 495, 15, 8, camX, camY);
    this->drawRectangle(renderer, 200, 200, 255, 120, 460, 15, 10, camX, camY);
    this->drawRectangle(renderer, 200, 200, 255, 145, 460, 15, 10, camX, camY);
}