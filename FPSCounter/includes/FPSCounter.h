#ifndef SCENEMANAGEMENT_FPSCOUNTER_H
#define SCENEMANAGEMENT_FPSCOUNTER_H
#include <string>

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>


class FPSCounter {
public:
    FPSCounter(SDL_Renderer* renderer, const std::string& fontPath, int fontSize);
    ~FPSCounter();

    void startFrame();

    void endFrame();

    void render();

    void toggleVisibility();

    int getFPS() const { return currentFPS; }

private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    Uint64 lastTime;
    int frameCount;
    int currentFPS;

    bool isVisible;

    void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y);
};


#endif //SCENEMANAGEMENT_FPSCOUNTER_H