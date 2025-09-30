//
// Created by jusra on 29-9-2025.
//

#include "../../include/Utils/Size.h"

Size::Size(int width, int height) {
    this->_width = width;
    this->_height = height;
}

int Size::getWidth() {
    return _width;
}

void Size::setWidth(int width) {
    this->_width = width;
}

int Size::getHeight() {
    return _height;
}

void Size::setHeight(int height) {
    this->_height = height;
}
