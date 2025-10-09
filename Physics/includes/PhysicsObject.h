#pragma once
#include <SDL3/SDL.h>
#include <box2d/box2d.h>
#include "Physics.h"

class PhysicsObject {
public:
    PhysicsObject(
        PhysicsWorld& physicsWorld,
        float topLeftX, float topLeftY,
        float width, float height,
        bool isDynamic = true
    );

    void update(float deltaTime) { (void)deltaTime; }

    void render(SDL_Renderer* renderer) const;

    void resetPosition(float topLeftX, float topLeftY);

    b2Body* getBody() { return m_physicsBody; }
    const b2Body* getBody() const { return m_physicsBody; }

private:
    PhysicsWorld& m_physicsWorld;
    b2Body* m_physicsBody = nullptr;
    float m_width;
    float m_height;
};