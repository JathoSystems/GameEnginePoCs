//
// Created by kikker234 on 03-10-2025.
//

#ifndef UIELEMENT_CAMERA_H
#define UIELEMENT_CAMERA_H

#include "../Scene.h"

class Camera {
private:
    int _x = 0, _y = 0; // positie van de camera in de wereld
    int width = 500, height = 500; // grootte van het viewport

public:
    int getX() const { return _x; }
    int getY() const { return _y; }
    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }

    void renderScene(Scene* scene, SDL_Renderer* renderer) {
        // Scene renderen, maar alle coordinates offsetten met _x, _y
        scene->render(renderer, _x, _y);
    }
};


#endif //UIELEMENT_CAMERA_H