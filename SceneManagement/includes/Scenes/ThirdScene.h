//
// Created by jusra on 1-10-2025.
//

#ifndef SCENEMANAGEMENT_THIRDSCENE_H
#define SCENEMANAGEMENT_THIRDSCENE_H

#include "../Scene.h"
#include <SDL3/SDL.h>

class ThirdScene : public Scene {
public:
    explicit ThirdScene(const std::string& name) : Scene(name) {}
    void render(SDL_Renderer* renderer) override;
};

#endif //SCENEMANAGEMENT_THIRDSCENE_H