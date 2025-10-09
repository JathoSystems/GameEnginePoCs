#pragma once
#include <box2d/box2d.h>

// Simple physics world facade
class Physics {
public:
    // pixels-per-meter (rendering uses pixels, physics uses meters)
    static constexpr float PPM = 100.0f;

    Physics(float gx = 0.0f, float gy = 9.81f);
    ~Physics() = default;

    // Fixed-step stepping helper
    void step(float dt);

    // Create a rectangular body (dynamic or static)
    b2Body* createBox(float x_px, float y_px, float w_px, float h_px, bool dynamic = true,
                      float density = 1.0f, float friction = 0.3f, float restitution = 0.0f);

    b2World& world() { return _world; }

private:
    b2World _world;
    // fixed step bookkeeping
    const float _timeStep = 1.0f / 60.0f;
    float _accumulator = 0.0f;
    int32 _velocityIterations = 8;
    int32 _positionIterations = 3;

    static float toMeters(float px) { return px / PPM; }
};
