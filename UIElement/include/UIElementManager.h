//
// Created by jusra on 30-9-2025.
//

#ifndef UIELEMENT_UIELEMENTMANAGER_H
#define UIELEMENT_UIELEMENTMANAGER_H
#include <memory>
#include <vector>

#include "Components/UIElement.h"
#include "Components/Window.h"

class UIElementManager {
private:
    std::vector<std::unique_ptr<UIElement>> _elements;
    SDL_Renderer *renderer;
    Window *window;

public:
    UIElementManager(Window *window);

    void addElement(std::unique_ptr<UIElement> element);

    void render();

    void update(float deltaTime);

    SDL_Renderer* getRenderer();
};

#endif //UIELEMENT_UIELEMENTMANAGER_H
