#include <iostream>
#include <SDL3/SDL.h>

#include "../includes/SceneManager.h"
#include "../includes/Scenes/FirstScene.h"
#include "../includes/Camera/Camera.h"

int main() {
    std::cout << "[INFO] Applicatie gestart" << std::endl;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "[ERROR] SDL initialisatie mislukt: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "[INFO] SDL geïnitialiseerd" << std::endl;

    SDL_Window *window = SDL_CreateWindow(
        "Scene management",
        500,
        500,
        SDL_WINDOW_OPENGL);

    if (!window) {
        std::cerr << "[ERROR] Window aanmaken mislukt: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    std::cout << "[INFO] Window aangemaakt (500x500)" << std::endl;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "[ERROR] Renderer aanmaken mislukt: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    std::cout << "[INFO] Renderer aangemaakt" << std::endl;

    FirstScene* scene = new FirstScene(" First scene");
    std::cout << "[INFO] Scene geladen: First scene" << std::endl;

    bool running = true;
    SDL_Event e;

    int currentScene = 0;

    // Camera
    Camera camera;
    std::cout << "[INFO] Camera geïnitialiseerd" << std::endl;
    std::cout << "[INFO] Game loop gestart. Druk op ESC of sluit het venster om af te sluiten." << std::endl;

    while (running) {
        // Event handling
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                std::cout << "[INFO] Quit event ontvangen" << std::endl;
                running = false;
            }
            if (e.type == SDL_EVENT_KEY_DOWN) {
                if (e.key.key == SDLK_ESCAPE) {
                    std::cout << "[INFO] ESC gedrukt - applicatie wordt afgesloten" << std::endl;
                    running = false;
                }
            }
        }

        // Verwerken input
        const bool* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT])  camera.setX(camera.getX() - 1);
        if (keys[SDL_SCANCODE_RIGHT]) camera.setX(camera.getX() + 1);
        if (keys[SDL_SCANCODE_UP])    camera.setY(camera.getY() - 1);
        if (keys[SDL_SCANCODE_DOWN])  camera.setY(camera.getY() + 1);

        SDL_RenderClear(renderer);
        camera.renderScene(scene, renderer);
        SDL_RenderPresent(renderer);
    }

    std::cout << "[INFO] Opruimen resources..." << std::endl;
    delete scene;
    std::cout << "[INFO] Scene verwijderd" << std::endl;

    SDL_DestroyRenderer(renderer);
    std::cout << "[INFO] Renderer vernietigd" << std::endl;

    SDL_DestroyWindow(window);
    std::cout << "[INFO] Window vernietigd" << std::endl;

    SDL_Quit();
    std::cout << "[INFO] SDL afgesloten" << std::endl;
    std::cout << "[INFO] Applicatie beëindigd" << std::endl;

    return 0;
}