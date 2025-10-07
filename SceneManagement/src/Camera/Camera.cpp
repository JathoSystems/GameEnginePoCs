//
// Created by jusra on 7-10-2025.
//
#include "../../includes/Camera/Camera.h"

Camera::Camera(int viewportWidth, int viewportHeight, int speed) {
    _viewportWidth = viewportWidth;
    _viewportHeight = viewportHeight;
    _speed = speed;
}

void Camera::moveLeft() {
    _x -= _speed;
}

void Camera::moveRight() {
    _x += _speed;
}

void Camera::moveUp() {
    _y -= _speed;
}

void Camera::moveDown() {
    _y += _speed;
}

void Camera::setPosition(int newX, int newY)  {
    _x = newX;
    _y = newY;
}

void Camera::setSpeed(int newSpeed) {
    _speed = newSpeed;
}

int Camera::getX() const {
    return _x;
}

int Camera::getY() const {
    return _y;
}

void Camera::moveTo(int targetX, int targetY, float smoothness)  {
    _x += static_cast<int>((targetX - _x) * smoothness);
    _y += static_cast<int>((targetY - _y) * smoothness);
}

void Camera::clampToBounds(int minX, int minY, int maxX, int maxY)  {
    if (_x < minX) _x = minX;
    if (_y < minY) _y = minY;
    if (_x > maxX - _viewportWidth) _x = maxX - _viewportWidth;
    if (_y > maxY - _viewportHeight) _y = maxY - _viewportHeight;
}

void Camera::renderScene(Scene *scene, SDL_Renderer *renderer) const  {
    if (scene) {
        scene->render(renderer, _x, _y);
    }
}

void Camera::reset()  {
    _x = 0;
    _y = 0;
}
