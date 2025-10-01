//
// Created by jusra on 1-10-2025.
//

#ifndef SCENEMANAGEMENT_SECONDSCENE_H
#define SCENEMANAGEMENT_SECONDSCENE_H

#include "../Scene.h"
#include <SDL3/SDL.h>

class SecondScene : public Scene {
public:
    explicit SecondScene(const std::string& name) : Scene(name) {}
    void render(SDL_Renderer* renderer) override;
};

#endif //SCENEMANAGEMENT_SECONDSCENE_H