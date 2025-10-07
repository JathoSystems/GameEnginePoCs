//
// Created by jusra on 1-10-2025.
//

#include <memory>

#include "../includes/Scene.h"
#include "../includes/SceneManager.h"

#include <iostream>

SceneManager::SceneManager(SDL_Renderer *renderer, int viewportWidth, int viewportHeight) {
    _renderer = renderer;
    _camera = std::make_unique<Camera>(viewportWidth, viewportHeight);
    activeScene = 0;
}

void SceneManager::openScene(Scene *scenePtr) {
    scenePtr->render(_renderer);
}

void SceneManager::addScene(std::unique_ptr<Scene> scene) {
    _scenes.push_back(std::move(scene));
}

std::vector<std::unique_ptr<Scene> > &SceneManager::getScenes() {
    return _scenes;
}

void SceneManager::switchScene(std::string sceneName) {
    this->resetCamera();

    int active = -1;
    for (int i = 0; i < _scenes.size(); ++i) {
        if (_scenes[i]->getName() == sceneName) {
            active = i;
            break;
        }
    }
    this->activeScene = active;
}

void SceneManager::render() {
    if (_scenes.empty()) {
        std::cout << "No scenes available." << std::endl;
        return;
    }
    if (activeScene < 0 || activeScene >= _scenes.size()) {
        std::cout << "No active scene found, default to first scene." << std::endl;
        activeScene = 0;
    }
    if (_camera) {
        _camera->renderScene(_scenes[activeScene].get(), _renderer);
    }
}

void SceneManager::handleInput(const SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        // Scene switching with number keys
        SDL_Keycode keycode = event.key.key;
        if (keycode >= SDLK_1 && keycode <= SDLK_9) {
            int sceneIndex = keycode - SDLK_1; // Convert to 0-based index
            if (sceneIndex < _scenes.size()) {
                activeScene = sceneIndex;
            }
        }
    }
}

void SceneManager::handleKeyboardInput(const bool *keyState) {
    if (!_camera) return;

    // Get shift state for speed modification
    bool isShiftPressed = keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT];
    int currentSpeed = isShiftPressed ? 15 : 7;
    _camera->setSpeed(currentSpeed);

    if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP]) {
        _camera->moveUp();
    }
    if (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN]) {
        _camera->moveDown();
    }
    if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) {
        _camera->moveLeft();
    }
    if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) {
        _camera->moveRight();
    }

    if (keyState[SDL_SCANCODE_R]) {
        _camera->reset();
    }
}

Camera *SceneManager::getCamera() {
    return _camera.get();
}

void SceneManager::resetCamera() {
    _camera->reset();
}

std::unique_ptr<Scene> &SceneManager::getCurrentScene() {
    return _scenes[activeScene];
}
