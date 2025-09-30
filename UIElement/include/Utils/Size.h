//
// Created by jusra on 29-9-2025.
//

#ifndef UIELEMENT_SIZE_H
#define UIELEMENT_SIZE_H


class Size {
private:
    int _width;
    int _height;

public:
    Size(int width, int height);

    int getWidth();

    void setWidth(int width);

    int getHeight();

    void setHeight(int height);
};


#endif //UIELEMENT_SIZE_H
