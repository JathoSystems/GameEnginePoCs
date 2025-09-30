//
// Created by jusra on 30-9-2025.
//

#include "../../include/Components/UIElement.h"
#include "../../include/Utils/Size.h"
#include "../../include/Utils/Position.h"
#include "../../include/Utils/Scale.h"
#include "../../include/Utils/Color.h"
#include "SDL3/SDL_render.h"

void UIElement::render(SDL_Renderer *renderer) {
  }

void UIElement::setLayer(int layer) {
    _layer = layer;
}

int UIElement::getLayer() {
    return _layer;
}

void UIElement::setSize(int width, int height) {
    if (!_size) _size = new Size(width, height);
    else {
        _size->setWidth(width);
        _size->setHeight(height);
    }
}

Size* UIElement::getSize() {
    return _size;
}

void UIElement::setPosition(int x, int y) {
    if (!_position) _position = new Position(x, y);
    else {
        _position->setX(x);
        _position->setY(y);
    }
}

Position* UIElement::getPosition() {
    return _position;
}

void UIElement::setScale(int scale) {
    if (!_scale) _scale = new Scale(scale);
    else _scale->setScale(scale);
}

Scale* UIElement::getScale() {
    return _scale;
}

void UIElement::setColor(int r, int g, int b) {
    if (!_color) _color = new Color(r, g, b);
    else {
        _color->setR(r);
        _color->setG(g);
        _color->setB(b);
    }
}

Color* UIElement::getColor() {
    return _color;
}