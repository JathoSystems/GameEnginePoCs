#pragma once
#include <SDL3/SDL.h>
#include <box2d/box2d.h>
#include "Physics.h"

// A drawable wrapper around a Box2D body (axis-aligned box)
class PhysicsObject {
public:
    PhysicsObject(Physics& physics, float x, float y, float width, float height, bool dynamic = true);

    // No per-object update needed (world steps in Physics::step), but keep for symmetry
    void update(float /*dt*/) {}

    void render(SDL_Renderer* renderer) const;

    // Reset to a starting pose (zero velocity)
    void reset(float x, float y);

    b2Body* body() { return _body; }

private:
    Physics& _physics;
    b2Body* _body = nullptr;

    // Store for rendering (in pixels)
    float _w, _h;
};
