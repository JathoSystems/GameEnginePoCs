//
// Created by jusra on 2-10-2025.
//

#ifndef UIELEMENT_KEYFRAME_H
#define UIELEMENT_KEYFRAME_H

#include "../Utils/Position.h"
#include "../Utils/Color.h"
#include "../Utils/Scale.h"

class Keyframe {
private:
    Position* _position = nullptr;
    Scale* _scale = nullptr;
    Color* _color = nullptr;

    bool _hasPosition = false;
    bool _hasScale = false;
    bool _hasColor = false;

public:
    Keyframe() = default;
    ~Keyframe();

    // Copy constructor en assignment operator
    Keyframe(const Keyframe& other);
    Keyframe& operator=(const Keyframe& other);

    void setPosition(int x, int y);
    Position* getPosition() const;
    bool hasPosition() const;

    void setScale(float scale);
    Scale* getScale() const;
    bool hasScale() const;

    void setColor(int r, int g, int b);
    Color* getColor() const;
    bool hasColor() const;
};

#endif //UIELEMENT_KEYFRAME_H