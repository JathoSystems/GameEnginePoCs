#include <vector>

#include "../include/Components/Window.h"
#include "../include/Components/Rectangle.h"
#include "../include/Components/Text.h"

#include <algorithm>
#include <SDL3/SDL.h>
#include <SDL3/SDL_timer.h>

#include "../include/Components/Sprite.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#include "../include/UIElementManager.h"

using namespace std;

int main() {
    int windowWidth = 800;
    int windowHeight = 600;

    auto window = std::make_unique<Window>();
    window->setSize(windowWidth, windowHeight);
    window->setColor(255, 255, 255);
    window->open("PoC UIElement");

    if (TTF_Init() == -1) {
        SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
        return -1;
    }

    UIElementManager manager{window.get()};

    auto rectangle = std::make_unique<Rectangle>();
    rectangle->setPosition(0, 0);
    rectangle->setSize(windowWidth, 100);
    rectangle->setColor(84, 158, 255);
    manager.addElement(std::move(rectangle));

    auto welcome = std::make_unique<Text>("Welcome, PoC!");
    welcome->setColor(255, 255, 255);
    welcome->setPosition(10, 10);
    welcome->setFontSize(50);
    welcome->setScale(2);
    manager.addElement(std::move(welcome));

    auto sprite = std::make_unique<Sprite>("../../assets/sprites/yellowNinja - attack.png");
    sprite->loadTexture(manager.getRenderer(), 0, 0, 20);
    sprite->setAnimationSpeed(20.0f);
    sprite->setPosition(0, 100);
    sprite->setScale(2);
    manager.addElement(std::move(sprite));

    bool done = false;
    Uint64 lastTime = SDL_GetTicks();

    while (!done) {
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; // in seconden
        lastTime = currentTime;

        // Event handling
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

        manager.update(deltaTime);
        manager.render();
    }


    window->close();
    TTF_Quit();

    return 0;
}
