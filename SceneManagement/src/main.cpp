#include <SDL3/SDL.h>
#include <iostream>
#include <memory>
#include "../includes/SceneManager.h"
#include "../includes/Scenes/CityScene.h"
#include "../includes/Scenes/HouseScene.h"

int main(int argc, char* argv[]) {
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    SDL_Window* window = SDL_CreateWindow(
        "Scene Viewer with Camera",
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SceneManager sceneManager(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    std::unique_ptr<HouseScene> houseScene = std::make_unique<HouseScene>("House Scene");
    houseScene->addButton(10, 10, 100, 40, [&sceneManager]() {
        sceneManager.resetCamera();
    }, {0, 255, 0, 255});

    houseScene->addButton(10, 60, 100, 40, [&sceneManager]() {
        sceneManager.switchScene("City Scene");
    }, {255, 0, 0, 255});

    std::unique_ptr<CityScene> cityScene = std::make_unique<CityScene>("City Scene");
    cityScene->addButton(10, 10, 100, 40, [&sceneManager]() {
        sceneManager.resetCamera();
    }, {0, 255, 0, 255});

    cityScene->addButton(10, 60, 100, 40, [&sceneManager]() {
        sceneManager.switchScene("House Scene");
    }, {255, 0, 0, 255});

    sceneManager.addScene(std::move(cityScene));
    sceneManager.addScene(std::move(houseScene));


    bool running = true;
    SDL_Event event;

    std::cout << "=== Controls ===" << std::endl;
    std::cout << "WASD or Arrow Keys: Move camera" << std::endl;
    std::cout << "Hold Shift: Move faster" << std::endl;
    std::cout << "R: Reset camera position" << std::endl;
    std::cout << "Click buttons for actions:" << std::endl;
    std::cout << "- Green button:\t\treset camera" << std::endl;
    std::cout << "- Red button:\t\tswitch scenes" << std::endl;
    std::cout << "================" << std::endl;

    // Main game loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                continue;
            }

            sceneManager.handleInput(event);

            Scene* currentScene = nullptr;
            if (!sceneManager.getScenes().empty()) {
                currentScene = sceneManager.getCurrentScene().get();
                if (currentScene) {
                    switch (event.type) {
                        case SDL_EVENT_MOUSE_MOTION:
                            currentScene->handleMouseMove(event.motion.x, event.motion.y);
                            break;
                        case SDL_EVENT_MOUSE_BUTTON_DOWN:
                            if (event.button.button == SDL_BUTTON_LEFT) {
                                currentScene->handleMouseClick(event.button.x, event.button.y);
                            }
                            break;
                    }
                }
            }
        }

        const bool* keyState = SDL_GetKeyboardState(nullptr);
        sceneManager.handleKeyboardInput(keyState);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        Scene* currentScene = nullptr;
        if (!sceneManager.getScenes().empty()) {
            currentScene = sceneManager.getCurrentScene().get();
        }
        if (currentScene) {
            sceneManager.render();
            currentScene->renderButtons(renderer);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
