//
// Created by jusra on 1-10-2025.
//

#ifndef SCENEMANAGEMENT_FIRSTSCENE_H
#define SCENEMANAGEMENT_FIRSTSCENE_H

#include "../Scene.h"
#include <SDL3/SDL.h>

class FirstScene : public Scene {
public:
    explicit FirstScene(const std::string& name) : Scene(name) {}
    void render(SDL_Renderer* renderer, int camX = 0, int camY = 0) override;
};

#endif //SCENEMANAGEMENT_FIRSTSCENE_H