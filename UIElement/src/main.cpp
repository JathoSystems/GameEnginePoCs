#include "../include/Window.h"
#include "../include/Color.h"
#include "../include/Text.h"
#include <SDL3/SDL.h>

#include "SDL3_ttf/SDL_ttf.h"

int main() {
    Window w{};
    w.open("PoC UIElement");

    // Initialiseer SDL_ttf
    if (!TTF_Init()) {
        SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
        return -1;
    }

    // Maak renderer aan
    SDL_Renderer* renderer = SDL_CreateRenderer(w.getSdlWindow(), nullptr);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        TTF_Quit();
        return -1;
    }

    auto* color = new Color(255, 255, 255);
    Text* text = new Text(color, "Hello world!");

    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

        // Clear de renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // zwart achtergrond
        SDL_RenderClear(renderer);

        // Render tekst
        text->render(renderer);

        // Toon alles op het scherm
        SDL_RenderPresent(renderer);
    }

    delete text;
    delete color;

    SDL_DestroyRenderer(renderer);
    w.close();

    // Sluit SDL_ttf af
    TTF_Quit();

    return 0;
}
