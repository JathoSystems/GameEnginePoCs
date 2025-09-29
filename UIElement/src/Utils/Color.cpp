//
// Created by jusra on 29-9-2025.
//

#include "../../include/Color.h"

Color::Color(int r, int g, int b) {
    this->_r = r;
    this->_g = g;
    this->_b = b;
}

int Color::getR() {
    return _r;
}

int Color::getG() {
    return _g;
}

int Color::getB() {
    return _b;
}

