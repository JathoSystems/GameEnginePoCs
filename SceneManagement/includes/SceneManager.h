//
// Created by jusra on 1-10-2025.
//

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include <vector>
#include <string>
#include <SDL3/SDL.h>
#include "../includes/Scene.h"
#include "../includes/Camera/Camera.h"

class SceneManager {
private:
    SDL_Renderer *_renderer;
    std::vector<std::unique_ptr<Scene> > _scenes;
    std::unique_ptr<Camera> _camera;
    int activeScene;

public:
    SceneManager(SDL_Renderer *renderer, int viewportWidth = 800, int viewportHeight = 600);

    void openScene(Scene *scenePtr);

    void addScene(std::unique_ptr<Scene> scene);

    std::vector<std::unique_ptr<Scene> > &getScenes();

    void switchScene(std::string sceneName);

    void render();

    void handleInput(const SDL_Event &event);

    void handleKeyboardInput(const bool *keyState);

    Camera *getCamera();
    void resetCamera();

    std::unique_ptr<Scene> &getCurrentScene();
};

#endif // SCENEMANAGER_H
