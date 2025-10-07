//
// Created by jusra on 7-10-2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <SDL3/SDL.h>
#include "../Scene.h"

class Camera {
private:
    int _x, _y;
    int _speed;
    int _viewportWidth, _viewportHeight;

public:
    Camera(int viewportWidth, int viewportHeight, int speed = 5);

    void moveLeft();

    void moveRight();

    void moveUp();

    void moveDown();

    void setPosition(int newX, int newY);

    void setSpeed(int newSpeed);

    int getX() const;

    int getY() const;

    void moveTo(int targetX, int targetY, float smoothness = 0.1f);

    void clampToBounds(int minX, int minY, int maxX, int maxY);

    void renderScene(Scene *scene, SDL_Renderer *renderer) const;

    void reset();
};

#endif // CAMERA_H
