//
// Created by jusra on 29-9-2025.
//

#include "../../include/Position.h"

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

int Position::getX() {
    return x;
}

int Position::getY() {
    return y;
}
