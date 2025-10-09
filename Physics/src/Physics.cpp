#include "Physics.h"

Physics::Physics(float gx, float gy)
    : _world(b2Vec2(gx, gy)) {}

void Physics::step(float dt) {
    _accumulator += dt;
    while (_accumulator >= _timeStep) {
        _world.Step(_timeStep, _velocityIterations, _positionIterations);
        _accumulator -= _timeStep;
    }
}

b2Body* Physics::createBox(float x_px, float y_px, float w_px, float h_px, bool dynamic,
                           float density, float friction, float restitution) {
    // Convert to meters; Box2D uses center-based coordinates
    float hw = 0.5f * w_px / PPM;
    float hh = 0.5f * h_px / PPM;

    b2BodyDef bd;
    bd.type = dynamic ? b2_dynamicBody : b2_staticBody;
    bd.position.Set(x_px / PPM + hw, y_px / PPM + hh); // place by top-left in pixels

    b2Body* body = _world.CreateBody(&bd);

    b2PolygonShape box;
    box.SetAsBox(hw, hh);

    b2FixtureDef fd;
    fd.shape = &box;
    fd.density = dynamic ? density : 0.0f;
    fd.friction = friction;
    fd.restitution = restitution;

    body->CreateFixture(&fd);
    return body;
}
