#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(Physics& physics, float x, float y, float width, float height, bool dynamic)
    : _physics(physics), _w(width), _h(height) {
    _body = _physics.createBox(x, y, width, height, dynamic);
}

void PhysicsObject::render(SDL_Renderer* renderer) const {
    // Read Box2D pose (meters) and convert to pixels
    b2Vec2 p = _body->GetPosition();
    float angle = _body->GetAngle(); // radians (ignored for axis-aligned fill)

    float centerX_px = p.x * Physics::PPM;
    float centerY_px = p.y * Physics::PPM;

    SDL_FRect rect;
    rect.w = _w;
    rect.h = _h;
    rect.x = centerX_px - _w * 0.5f;
    rect.y = centerY_px - _h * 0.5f;

    // For simplicity, draw as axis-aligned box (no rotation rendering here)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void PhysicsObject::reset(float x, float y) {
    // Set transform (meters) and zero velocities
    float hw = 0.5f * _w / Physics::PPM;
    float hh = 0.5f * _h / Physics::PPM;
    _body->SetTransform(b2Vec2((x / Physics::PPM) + hw, (y / Physics::PPM) + hh), 0.0f);
    _body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    _body->SetAngularVelocity(0.0f);
    _body->SetAwake(true);
}
