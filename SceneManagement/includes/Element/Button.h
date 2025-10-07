//
// Created by jusra on 7-10-2025.
//

#ifndef SCENEMANAGEMENT_BUTTON_H
#define SCENEMANAGEMENT_BUTTON_H
#include <functional>
#include <string>

#include "SDL3/SDL_pixels.h"

class Button {
private:
    int _x, _y, _width, _height;
    SDL_Color _bgColor;
    std::function<void()> _onClick;
    bool _isHovered;

public:
    Button(int x, int y, int width, int height, std::function<void()> onClick,
           SDL_Color bgColor = {100, 100, 100, 255});

    bool contains(int mouseX, int mouseY) const;

    bool isHovered() const;

    void setHovered(bool hovered);

    void click();

    int getX() const;

    int getY() const;

    SDL_Color getBackgroundColor() const;

    int getHeight() const;

    int getWidth() const;
};
#endif //SCENEMANAGEMENT_BUTTON_H
