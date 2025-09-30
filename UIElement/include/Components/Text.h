//
// Created by jusra on 29-9-2025.
//

#ifndef UIELEMENT_TEXT_H
#define UIELEMENT_TEXT_H
#include <string>

#include "UIElement.h"
#include "../Utils/Color.h"
#include "SDL3/SDL_render.h"

class Text : public UIElement {
private:
    int _fontSize = 30;
    std::string _text;

public:
    Text(std::string text);

    void render(SDL_Renderer *renderer) override;

    int getFontSize();

    std::string getText();

    void setText(std::string text);

    void setFontSize(int fontSize);
};

#endif //UIELEMENT_TEXT_H
