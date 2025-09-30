//
// Created by jusra on 29-9-2025.
//

#include "../../include/Utils/Color.h"

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

void Color::setR(int r) {
    this->_r = r;
}

void Color::setG(int g) {
    this->_g = g;
}

void Color::setB(int b) {
    this->_b = b;
}

