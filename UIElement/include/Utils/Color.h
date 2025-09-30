//
// Created by jusra on 29-9-2025.
//

#ifndef UIELEMENT_COLOR_H
#define UIELEMENT_COLOR_H


class Color {
private:
    int _r;
    int _g;
    int _b;

public:
    Color(int r, int g, int b);

    int getR();

    int getG();

    int getB();

    void setR(int r);

    void setG(int g);

    void setB(int b);
};


#endif //UIELEMENT_COLOR_H
