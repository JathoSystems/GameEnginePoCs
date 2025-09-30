//
// Created by jusra on 30-9-2025.
//

#ifndef UIELEMENT_UIELEMENT_H
#define UIELEMENT_UIELEMENT_H
#include "../Utils/Size.h"
#include "../Utils/Position.h"
#include "../Utils/Scale.h"
#include "../Utils/Color.h"
#include "SDL3/SDL_render.h"

class UIElement {
protected:
    int _layer = 1;
    Size *_size = new Size(10, 10);
    Position *_position = new Position(0, 0);
    Scale *_scale = new Scale(1);
    Color *_color = new Color(255, 255, 255);

public:
    virtual ~UIElement() {
        delete _size;
        delete _position;
        delete _scale;
    }

    virtual void render(SDL_Renderer *renderer);

    void setLayer(int layer);

    int getLayer();

    void setSize(int width, int height);

    Size *getSize();

    void setPosition(int x, int y);

    Position *getPosition();

    void setScale(int scale);

    Scale *getScale();

    void setColor(int r, int g, int b);

    Color *getColor();
};

#endif //UIELEMENT_UIELEMENT_H
