//
// Created by jusra on 1-10-2025.
//

#ifndef UIELEMENT_SCENEMANAGER_H
#define UIELEMENT_SCENEMANAGER_H
#include <memory>
#include <vector>
#include "Scene.h"

class SceneManager {
private:
    std::vector<std::unique_ptr<Scene>> _scenes;
    SDL_Renderer* _renderer;
public:
    SceneManager(SDL_Renderer* renderer);
    void openScene(Scene *scenePtr);

    void addScene(std::unique_ptr<Scene> scene);

    std::vector<std::unique_ptr<Scene>>& getScenes();

    Scene *getByName(std::string name);
};

#endif //UIELEMENT_SCENEMANAGER_H