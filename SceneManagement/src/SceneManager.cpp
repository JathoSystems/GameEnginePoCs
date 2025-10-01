//
// Created by jusra on 1-10-2025.
//

#include <memory>

#include "../includes/Scene.h"
#include "../includes/SceneManager.h"

SceneManager::SceneManager(SDL_Renderer *renderer) {
    _renderer = renderer;
}

void SceneManager::openScene(Scene* scenePtr) {
    scenePtr->render(_renderer);
}

void SceneManager::addScene(std::unique_ptr<Scene> scene) {
    _scenes.push_back(std::move(scene));
}

std::vector<std::unique_ptr<Scene>>& SceneManager::getScenes() {
    return _scenes;
}

Scene *SceneManager::getByName(std::string name) {
    for (const std::unique_ptr<Scene>& scene : getScenes()) {
        if (scene->getName() == name) {
            return scene.get();
        }
    }

    return nullptr;
}
