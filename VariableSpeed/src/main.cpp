#include <iostream>
#include <SDL3/SDL.h>

#include "../includes/Time.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL kon niet geïnitialiseerd worden: " << SDL_GetError() << std::endl;
        return 1;
    }

    const int windowWidth = 800;
    const int windowHeight = 600;

    SDL_Window *window = SDL_CreateWindow("Variable Speed (-) Decrease (=) Increase", windowWidth, windowHeight, SDL_WINDOW_OPENGL);
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

    bool running = true;
    SDL_Event e;

    bool directionRight = true;

    while (running) {

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (e.type == SDL_EVENT_KEY_DOWN) {
                if (e.key.key == SDLK_EQUALS) {
                    Time::instance().increaseModifier(0.25);
                    std::cout << "Speed Modifier: " << Time::instance().getModifier() << std::endl;
                }
                if (e.key.key == SDLK_MINUS) {
                    Time::instance().decreaseModifier(0.25);
                    std::cout << "Speed Modifier: " << Time::instance().getModifier() << std::endl;
                }
            }
        }

        SDL_RenderClear(renderer);

        static float rectX = 100.0f;
        const float rectY = 250.0f;
        const int rectW = 100;
        const int rectH = 50;

        const float baseSpeed = 200.0f;
        float speed = baseSpeed * Time::instance().getModifier();

        static Uint64 lastTicks = SDL_GetTicks();
        Uint64 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - lastTicks) / 1000.0f;
        lastTicks = currentTicks;

        if (directionRight) rectX += speed * deltaTime;
        else rectX -= speed * deltaTime;

        if (rectX < 0) {
            rectX = 0;
            directionRight = true;
        } else if (rectX + rectW > windowWidth) {
            rectX = windowWidth - rectW;
            directionRight = false;
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_FRect rect = { rectX, rectY, static_cast<float>(rectW), static_cast<float>(rectH) };
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
