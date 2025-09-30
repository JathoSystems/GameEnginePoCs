#include <vector>

#include "../include/Components/Window.h"
#include "../include/Components/Rectangle.h"
#include "../include/Components/Text.h"

#include <algorithm>
#include <SDL3/SDL.h>

#include "SDL3_ttf/SDL_ttf.h"

using namespace std;

int main() {
    vector<UIElement*> UIElements;
    Window w{};
    w.open("PoC UIElement");

    if (!TTF_Init()) {
        SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(w.getSdlWindow(), nullptr);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        TTF_Quit();
        return -1;
    }
    Text* text2 = new Text("Appel!");
    text2->setColor(0, 255, 0);
    text2->setPosition(100, 0);
    text2->setScale(3);
    text2->setFontSize(30);
    text2->setLayer(10);
    UIElements.push_back(text2);

    Text* text = new Text("Hello world!");
    text->setLayer(5);
    text->setPosition(100, 0);
    text->setScale(3);
    text->setFontSize(30);
    text->setColor(0, 0, 0);

    UIElements.push_back(text);

    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderClear(renderer);

        std::sort(UIElements.begin(), UIElements.end(), [](UIElement* a, UIElement* b) {
            return a->getLayer() < b->getLayer();
        });

        for (auto ui_element : UIElements)
            ui_element->render(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    w.close();

    for (UIElement* element : UIElements) delete element;
    UIElements.clear();

    TTF_Quit();

    return 0;
}
