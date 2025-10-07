//
// Created by jusra on 1-10-2025.
//

#ifndef SCENEMANAGEMENT_CITYSCENE_H
#define SCENEMANAGEMENT_CITYSCENE_H

#include "../Scene.h"
#include <SDL3/SDL.h>

class CityScene : public Scene {
public:
    explicit CityScene(const std::string &name) : Scene(name) {
    }

    void render(SDL_Renderer *renderer, int camX = 0, int camY = 0) override;
};

#endif //SCENEMANAGEMENT_CITYSCENE_H
