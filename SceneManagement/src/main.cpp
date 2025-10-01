#include <iostream>
#include <ostream>
#include <SDL3/SDL.h>

#include "../includes/SceneManager.h"
#include "../includes/Scenes/FirstScene.h"
#include "../includes/Scenes/SecondScene.h"
#include "../includes/Scenes/ThirdScene.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Scene management",
        500,
        500,
        SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    SceneManager manager{renderer};

    std::unique_ptr<Scene> first = std::make_unique<FirstScene>("FirstScene");
    std::unique_ptr<Scene> second = std::make_unique<SecondScene>("SecondScene");
    std::unique_ptr<Scene> third = std::make_unique<ThirdScene>("ThirdScene");

    manager.addScene(std::move(first));
    manager.addScene(std::move(second));
    manager.addScene(std::move(third));

    std::vector<std::unique_ptr<Scene> > &scenes = manager.getScenes();

    bool running = true;
    SDL_Event e;

    Uint64 lastSwitch = SDL_GetTicks();
    int currentScene = 0;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        Uint64 now = SDL_GetTicks();
        if (now - lastSwitch >= 2000) {
            currentScene = (currentScene + 1) % scenes.size();
            lastSwitch = now;
        }
        std::unique_ptr<Scene> &scene = scenes[currentScene];
        manager.openScene(scene.get());
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
