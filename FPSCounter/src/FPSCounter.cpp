#include "../includes/FPSCounter.h"
#include <iostream>

#include "SDL3/SDL_timer.h"

void FPSCounter::renderText(SDL_Renderer *ren, const std::string &text, int x, int y) {
    if (!font) return;

    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), 0, color);
    if (!surface) {
        std::cerr << "TTF_RenderText_Solid Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_DestroySurface(surface);
        return;
    }

    SDL_FRect dest = { (float)x, (float)y, (float)surface->w, (float)surface->h };

    SDL_RenderTexture(ren, texture, nullptr, &dest);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

FPSCounter::FPSCounter(SDL_Renderer *renderer, const std::string &fontPath, int fontSize)
    : renderer(renderer),
      lastTime(SDL_GetTicks()),
      frameCount(0),
      currentFPS(0),
      isVisible(true)
{
    if (TTF_WasInit() == 0) {
        if (TTF_Init() == -1) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
        }
    }

    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        std::cerr << "TTF_OpenFont Error: " << SDL_GetError() << std::endl;
    }
}

FPSCounter::~FPSCounter() {
    if (font) {
        TTF_CloseFont(font);
    }
}

void FPSCounter::startFrame() {
    // Intentionally left empty
}

void FPSCounter::endFrame() {
    frameCount++;
    Uint64 currentTime = SDL_GetTicks();
    if (currentTime - lastTime >= 1000) {
        currentFPS = frameCount;
        frameCount = 0;
        lastTime = currentTime;
    }
}

void FPSCounter::render() {
    if (!isVisible || !renderer) return;

    std::string fpsText = std::to_string(currentFPS) + " FPS";

    renderText(renderer, fpsText, 10, 10);
}

void FPSCounter::toggleVisibility() {
    isVisible = !isVisible;
    std::cout << "FPS Visible: " << isVisible << std::endl;
}