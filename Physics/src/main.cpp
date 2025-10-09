// main.cpp — SDL3 diagnostics + Box2D demo (fixed for SDL3 APIs)
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>  // SDL3 migration: include this in the file with main()
#include <SDL3/SDL_version.h>
#include <cstdio>

#include "Physics.h"
#include "PhysicsObject.h"

static void log_sdl_drivers() {
    const int compiled = SDL_VERSION;       // from headers
    const int linked   = SDL_GetVersion();  // from linked library

    SDL_Log("SDL compiled: %d.%d.%d  linked: %d.%d.%d",
            SDL_VERSIONNUM_MAJOR(compiled), SDL_VERSIONNUM_MINOR(compiled), SDL_VERSIONNUM_MICRO(compiled),
            SDL_VERSIONNUM_MAJOR(linked),   SDL_VERSIONNUM_MINOR(linked),   SDL_VERSIONNUM_MICRO(linked));

    // Render drivers available (names only in SDL3)
    const int n = SDL_GetNumRenderDrivers();
    SDL_Log("Render drivers available: %d", n);
    for (int i = 0; i < n; ++i) {
        const char* name = SDL_GetRenderDriver(i);
        SDL_Log("  - %s", name ? name : "(null)");
    }
}

static SDL_Renderer* try_create_renderer(SDL_Window* window, const char* name_hint) {
    if (name_hint) SDL_Log("Trying renderer: %s", name_hint);
    SDL_Renderer* r = SDL_CreateRenderer(window, name_hint); // SDL3: second arg is name (or NULL)
    if (!r) SDL_Log("SDL_CreateRenderer%s%s failed: %s",
                    name_hint ? "('" : "", name_hint ? name_hint : "", SDL_GetError());
    return r;
}

int main(int, char**) {
    log_sdl_drivers();

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        SDL_Log("Hints: ensure Cocoa/Metal backends (install full Xcode), not headless, consider pinning a release tag.");
        return 1;
    }
    SDL_Log("Video driver in use: %s", SDL_GetCurrentVideoDriver());

    SDL_Window* window = SDL_CreateWindow("Physics PoC (SDL3 diag)", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Try a few likely renderers on macOS
#if defined(__APPLE__)
    const char* order[] = {"metal", "opengl", nullptr};
#else
    const char* order[] = {"opengl", nullptr};
#endif

    SDL_Renderer* renderer = nullptr;
    for (const char** p = order; *p || p == order; ++p) {
        renderer = try_create_renderer(window, *p);
        if (renderer) break;
        if (!*p) break; // last attempt was NULL (let SDL choose)
    }
    if (!renderer) {
        SDL_Log("No renderer could be created. Aborting.");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    const char* active = SDL_GetRendererName(renderer);
    SDL_Log("Renderer created: %s", active ? active : "(unknown)");

    // --------- Box2D world ----------
    Physics physics(0.0f, 9.81f);
    const float groundY = 580.0f;
    (void) physics.createBox(0.0f, groundY, 800.0f, 20.0f, /*dynamic=*/false, 0.0f, 0.6f, 0.0f);
    PhysicsObject cube(physics, 350.0f, 100.0f, 50.0f, 50.0f, /*dynamic=*/true);

    bool running = true;
    SDL_Event ev;
    uint64_t prev = SDL_GetTicksNS();

    while (running) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_EVENT_QUIT) running = false;
            if (ev.type == SDL_EVENT_KEY_DOWN && ev.key.key == SDLK_SPACE) {
                cube.reset(350.0f, 100.0f);
            }
        }

        uint64_t now = SDL_GetTicksNS();
        float dt = float(now - prev) / 1'000'000'000.0f;
        prev = now;

        physics.step(dt);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_FRect groundRect{0.0f, groundY, 800.0f, 20.0f};
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        SDL_RenderFillRect(renderer, &groundRect);

        cube.render(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
