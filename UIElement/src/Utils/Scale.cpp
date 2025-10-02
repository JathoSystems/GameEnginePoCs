//
// Created by jusra on 29-9-2025.
//

#include "../../include/Utils/Scale.h"

Scale::Scale(float scale) {
    this->scale = scale;
}

float Scale::getScale() {
    return scale;
}

void Scale::setScale(float scale) {
    this->scale = scale;
}
