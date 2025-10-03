#include <iostream>
#include <ostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "../includes/FPSCounter.h"

#define FONT_PATH "../../assets/fonts/OpenSans.ttf"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL kon niet geïnitialiseerd worden: " << SDL_GetError() << std::endl;
        return 1;
    }

    const int windowWidth = 800;
    const int windowHeight = 600;

    SDL_Window *window = SDL_CreateWindow("FPS Counter (Toggle F9)", windowWidth, windowHeight, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "Window kon niet aangemaakt worden: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "Renderer kon niet aangemaakt worden: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_SetRenderVSync(renderer, 1);

    FPSCounter fpsCounter(renderer, FONT_PATH, 24);

    bool running = true;
    SDL_Event e;

    while (running) {
        Uint64 frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (e.type == SDL_EVENT_KEY_DOWN) {
                // F9 om FPS-teller te toggelen
                if (e.key.key == SDLK_F9) {
                    fpsCounter.toggleVisibility();
                }
            }
        }

        fpsCounter.startFrame();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        fpsCounter.render();

        SDL_RenderPresent(renderer);

        fpsCounter.endFrame();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
