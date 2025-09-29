//
// Created by jusra on 29-9-2025.
//

#include "../../include/Size.h"

Size::Size(int width, int height) {
    this->_width = width;
    this->_height = height;
}

int Size::getWidth() {
    return _width;
}

int Size::getHeight() {
    return _height;
}
