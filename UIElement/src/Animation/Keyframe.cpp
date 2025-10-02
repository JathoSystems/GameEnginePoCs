//
// Created by jusra on 2-10-2025.
//

#include "../../include/Animation/Keyframe.h"

Keyframe::~Keyframe() {
    delete _position;
    delete _scale;
    delete _color;
}

Keyframe::Keyframe(const Keyframe& other) {
    _hasPosition = other._hasPosition;
    _hasScale = other._hasScale;
    _hasColor = other._hasColor;

    if (other._position) {
        _position = new Position(*other._position);
    } else {
        _position = nullptr;
    }

    if (other._scale) {
        _scale = new Scale(*other._scale);
    } else {
        _scale = nullptr;
    }

    if (other._color) {
        _color = new Color(*other._color);
    } else {
        _color = nullptr;
    }
}

Keyframe& Keyframe::operator=(const Keyframe& other) {
    if (this != &other) {
        delete _position;
        delete _scale;
        delete _color;

        _hasPosition = other._hasPosition;
        _hasScale = other._hasScale;
        _hasColor = other._hasColor;

        if (other._position) {
            _position = new Position(*other._position);
        } else {
            _position = nullptr;
        }

        if (other._scale) {
            _scale = new Scale(*other._scale);
        } else {
            _scale = nullptr;
        }

        if (other._color) {
            _color = new Color(*other._color);
        } else {
            _color = nullptr;
        }
    }
    return *this;
}

void Keyframe::setPosition(int x, int y) {
    if (!_position) {
        _position = new Position(x, y);
    } else {
        _position->setX(x);
        _position->setY(y);
    }
    _hasPosition = true;
}

Position* Keyframe::getPosition() const {
    return _position;
}

bool Keyframe::hasPosition() const {
    return _hasPosition;
}

void Keyframe::setScale(float scale) {
    if (!_scale) {
        _scale = new Scale(scale);
    } else {
        _scale->setScale(scale);
    }
    _hasScale = true;
}

Scale* Keyframe::getScale() const {
    return _scale;
}

bool Keyframe::hasScale() const {
    return _hasScale;
}

void Keyframe::setColor(int r, int g, int b) {
    if (!_color) {
        _color = new Color(r, g, b);
    } else {
        _color->setR(r);
        _color->setG(g);
        _color->setB(b);
    }
    _hasColor = true;
}

Color* Keyframe::getColor() const {
    return _color;
}

bool Keyframe::hasColor() const {
    return _hasColor;
}