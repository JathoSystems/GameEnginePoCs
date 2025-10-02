//
// Created by jusra on 30-9-2025.
//

#include "../include/UIElementManager.h"

#include <algorithm>
#include <iostream>

UIElementManager::UIElementManager(Window *window) {
    this->window = window;
    this->renderer = SDL_CreateRenderer(window->getSdlWindow(), nullptr);
}


void UIElementManager::addElement(std::unique_ptr<UIElement> element) {
    _elements.emplace_back(std::move(element));


    std::sort(_elements.begin(), _elements.end(),
        [](const std::unique_ptr<UIElement>& a, const std::unique_ptr<UIElement>& b) {
            return a->getLayer() < b->getLayer();
        }
    );
}

void UIElementManager::render() {
    Color* color = window->getColor();
    SDL_SetRenderDrawColor(renderer, color->getR(), color->getG(), color->getB(), 255);
    SDL_RenderClear(renderer);

    for (const std::unique_ptr<UIElement>& element : this->_elements)
        element->render(this->renderer);

    SDL_RenderPresent(renderer);
}

void UIElementManager::update(float deltaTime) {
    for (const std::unique_ptr<UIElement>& element : _elements) {
        element->update(deltaTime); // Sprite::update wordt hier aangeroepen
    }
}



SDL_Renderer * UIElementManager::getRenderer() {
    return this->renderer;
}
