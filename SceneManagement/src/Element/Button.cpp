//
// Created by jusra on 7-10-2025.
//

#include <utility>

#include "./../../includes/Element/Button.h";

Button::Button(int x, int y, int width, int height, std::function<void()> onClick, SDL_Color bgColor) {
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _onClick = std::move(onClick);
    _bgColor = bgColor;
    _isHovered = false;
}

bool Button::contains(int mouseX, int mouseY) const {
    return mouseX >= _x && mouseX <= _x + _width &&
           mouseY >= _y && mouseY <= _y + _height;
}

bool Button::isHovered() const {
    return _isHovered;
}

void Button::setHovered(bool hovered) {
    _isHovered = hovered;
}

void Button::click() {
    _onClick();
}

int Button::getX() const {
    return _x;
}

int Button::getY() const {
    return _y;
}

SDL_Color Button::getBackgroundColor() const {
    return _bgColor;
}

int Button::getHeight() const {
    return _height;
}

int Button::getWidth() const {
    return _width;
}
