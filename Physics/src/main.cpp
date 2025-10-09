#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Physics.h"
#include "PhysicsObject.h"
#include "PlayerController.h"

namespace {
    constexpr int WINDOW_WIDTH = 1000;
    constexpr int WINDOW_HEIGHT = 700;
    constexpr const char* WINDOW_TITLE = "Physics PoC";
    
    constexpr float MAP_WIDTH = 1000.0f;
    constexpr float FLOOR_Y = 660.0f;
    constexpr float GRAVITY_Y = 20.0f;
    
    constexpr float LEFT_RAMP_BASE = 280.0f;
    constexpr float LEFT_RAMP_HEIGHT = 140.0f;
    constexpr float LEFT_RAMP_MARGIN = 10.0f;
    
    constexpr float RIGHT_RAMP_BASE = 240.0f;
    constexpr float RIGHT_RAMP_HEIGHT = 160.0f;
    constexpr float RIGHT_RAMP_MARGIN = 10.0f;
    
    constexpr float BOX_X = 600.0f;
    constexpr float BOX_SIZE = 70.0f;
    constexpr float BOX_FRICTION = 0.45f;
    constexpr float BOX_DENSITY = 1.6f;
    constexpr float BOX_LINEAR_DAMPING = 0.45f;
    constexpr float BOX_ANGULAR_DAMPING = 5.0f;
    
    constexpr float PLAYER_START_X = 150.0f;
    constexpr float PLAYER_WIDTH = 50.0f;
    constexpr float PLAYER_HEIGHT = 70.0f;
    constexpr float PLAYER_FRICTION = 1.0f;
    constexpr float PLAYER_LINEAR_DAMPING = 2.0f;
    
    constexpr SDL_Color BACKGROUND_COLOR = {22, 22, 26, 255};
    constexpr SDL_Color FLOOR_COLOR = {80, 80, 90, 255};
    constexpr SDL_Color LEFT_RAMP_COLOR = {100, 200, 100, 255};
    constexpr SDL_Color RIGHT_RAMP_COLOR = {200, 120, 100, 255};

    void renderTriangle(
        SDL_Renderer* renderer,
        float centerX, float centerY,
        float x0, float y0, float x1, float y1, float x2, float y2,
        SDL_Color color
    ) {
        SDL_Vertex vertices[3];
        
        auto setVertex = [&](int index, float x, float y) {
            vertices[index].position.x = centerX + x;
            vertices[index].position.y = centerY + y;
            vertices[index].color = SDL_FColor{
                color.r / 255.f, 
                color.g / 255.f, 
                color.b / 255.f, 
                color.a / 255.f
            };
        };
        
        setVertex(0, x0, y0);
        setVertex(1, x1, y1);
        setVertex(2, x2, y2);
        
        SDL_RenderGeometry(renderer, nullptr, vertices, 3, nullptr, 0);
    }

    void renderLeftRamp(SDL_Renderer* renderer, b2Body* rampBody) {
        b2Vec2 position = rampBody->GetPosition();
        const float centerX = position.x * PhysicsWorld::PIXELS_PER_METER;
        const float centerY = position.y * PhysicsWorld::PIXELS_PER_METER;
        
        renderTriangle(
            renderer, centerX, centerY,
            +LEFT_RAMP_BASE * 0.5f, 0.0f,
            -LEFT_RAMP_BASE * 0.5f, 0.0f,
            -LEFT_RAMP_BASE * 0.5f, -LEFT_RAMP_HEIGHT,
            LEFT_RAMP_COLOR
        );
    }

    void renderRightRamp(SDL_Renderer* renderer, b2Body* rampBody) {
        b2Vec2 position = rampBody->GetPosition();
        const float centerX = position.x * PhysicsWorld::PIXELS_PER_METER;
        const float centerY = position.y * PhysicsWorld::PIXELS_PER_METER;
        
        renderTriangle(
            renderer, centerX, centerY,
            -RIGHT_RAMP_BASE * 0.5f, 0.0f,
            +RIGHT_RAMP_BASE * 0.5f, 0.0f,
            +RIGHT_RAMP_BASE * 0.5f, -RIGHT_RAMP_HEIGHT,
            RIGHT_RAMP_COLOR
        );
    }
}

int main(int, char**) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        WINDOW_TITLE, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, "metal");
    if (!renderer) {
        renderer = SDL_CreateRenderer(window, nullptr);
    }
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    PhysicsWorld physicsWorld(0.0f, GRAVITY_Y);

    physicsWorld.createRectangleBody(
        0.0f, FLOOR_Y, 
        MAP_WIDTH, 40.0f, 
        false,
        0.0f, 0.9f, 0.0f
    );

    const float leftRampCenterX = (LEFT_RAMP_BASE * 0.5f) + LEFT_RAMP_MARGIN;
    b2Body* leftRamp = physicsWorld.createTriangleRamp(
        leftRampCenterX, FLOOR_Y,
        LEFT_RAMP_BASE, LEFT_RAMP_HEIGHT,
        false,
        1.0f
    );

    const float rightRampCenterX = MAP_WIDTH - (RIGHT_RAMP_BASE * 0.5f) - RIGHT_RAMP_MARGIN;
    b2Body* rightRamp = physicsWorld.createTriangleRamp(
        rightRampCenterX, FLOOR_Y,
        RIGHT_RAMP_BASE, RIGHT_RAMP_HEIGHT,
        true,
        1.0f
    );

    PhysicsObject pushableBox(
        physicsWorld, 
        BOX_X, FLOOR_Y - BOX_SIZE, 
        BOX_SIZE, BOX_SIZE, 
        true
    );
    
    for (b2Fixture* fixture = pushableBox.getBody()->GetFixtureList();
         fixture != nullptr; 
         fixture = fixture->GetNext()) {
        fixture->SetFriction(BOX_FRICTION);
        fixture->SetDensity(BOX_DENSITY);
    }
    pushableBox.getBody()->ResetMassData();
    pushableBox.getBody()->SetFixedRotation(true);
    pushableBox.getBody()->SetLinearDamping(BOX_LINEAR_DAMPING);
    pushableBox.getBody()->SetAngularDamping(BOX_ANGULAR_DAMPING);

    PhysicsObject player(
        physicsWorld, 
        PLAYER_START_X, FLOOR_Y - PLAYER_HEIGHT - 20.0f, 
        PLAYER_WIDTH, PLAYER_HEIGHT, 
        true
    );
    player.getBody()->SetFixedRotation(true);
    player.getBody()->SetLinearDamping(PLAYER_LINEAR_DAMPING);
    
    for (b2Fixture* fixture = player.getBody()->GetFixtureList(); 
         fixture != nullptr; 
         fixture = fixture->GetNext()) {
        fixture->SetFriction(PLAYER_FRICTION);
    }

    physicsWorld.setPlayerBody(player.getBody());
    PlayerController playerController;
    playerController.setBody(player.getBody());

    bool isRunning = true;
    SDL_Event event;
    uint64_t previousTime = SDL_GetTicksNS();

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                isRunning = false;
            }
            playerController.handleInput(event);
        }

        const uint64_t currentTime = SDL_GetTicksNS();
        const float deltaTime = static_cast<float>(currentTime - previousTime) / 1'000'000'000.0f;
        previousTime = currentTime;

        playerController.update(physicsWorld, deltaTime);
        physicsWorld.stepSimulation(deltaTime);

        SDL_SetRenderDrawColor(
            renderer, 
            BACKGROUND_COLOR.r, 
            BACKGROUND_COLOR.g, 
            BACKGROUND_COLOR.b, 
            BACKGROUND_COLOR.a
        );
        SDL_RenderClear(renderer);

        SDL_FRect floorRect{0, FLOOR_Y, MAP_WIDTH, 40};
        SDL_SetRenderDrawColor(
            renderer, 
            FLOOR_COLOR.r, 
            FLOOR_COLOR.g, 
            FLOOR_COLOR.b, 
            FLOOR_COLOR.a
        );
        SDL_RenderFillRect(renderer, &floorRect);

        renderLeftRamp(renderer, leftRamp);
        renderRightRamp(renderer, rightRamp);

        pushableBox.render(renderer);
        player.render(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}