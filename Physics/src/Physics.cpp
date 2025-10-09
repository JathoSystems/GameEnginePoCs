#include "Physics.h"
#include <cmath>

namespace {
    inline float degreesToRadians(float degrees) {
        return degrees * 3.14159265358979323846f / 180.0f;
    }

    constexpr float GROUND_NORMAL_THRESHOLD = 0.3f;
}

PhysicsWorld::PhysicsWorld(float gravityX, float gravityY)
    : m_world(b2Vec2(gravityX, gravityY)) {
    m_world.SetContactListener(this);
}

void PhysicsWorld::stepSimulation(float deltaTime) {
    m_timeAccumulator += deltaTime;

    while (m_timeAccumulator >= FIXED_TIMESTEP) {
        m_world.Step(FIXED_TIMESTEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
        m_timeAccumulator -= FIXED_TIMESTEP;
    }
}

b2Body* PhysicsWorld::createRectangleBody(
    float topLeftX, float topLeftY,
    float width, float height,
    bool isDynamic,
    float density,
    float friction,
    float bounciness
) {
    const float halfWidth = 0.5f * pixelsToMeters(width);
    const float halfHeight = 0.5f * pixelsToMeters(height);

    b2BodyDef bodyDefinition;
    bodyDefinition.type = isDynamic ? b2_dynamicBody : b2_staticBody;

    bodyDefinition.position.Set(
        pixelsToMeters(topLeftX) + halfWidth,
        pixelsToMeters(topLeftY) + halfHeight
    );

    b2Body* body = m_world.CreateBody(&bodyDefinition);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(halfWidth, halfHeight);

    b2FixtureDef fixtureDefinition;
    fixtureDefinition.shape = &boxShape;
    fixtureDefinition.density = isDynamic ? density : 0.0f;
    fixtureDefinition.friction = friction;
    fixtureDefinition.restitution = bounciness;

    body->CreateFixture(&fixtureDefinition);
    return body;
}

b2Body* PhysicsWorld::createRotatedRamp(
    float centerX, float centerY,
    float width, float height,
    float rotationDegrees,
    float friction
) {
    const float halfWidth = 0.5f * pixelsToMeters(width);
    const float halfHeight = 0.5f * pixelsToMeters(height);

    b2BodyDef bodyDefinition;
    bodyDefinition.type = b2_staticBody;
    bodyDefinition.position = b2Vec2(pixelsToMeters(centerX), pixelsToMeters(centerY));
    bodyDefinition.angle = degreesToRadians(rotationDegrees);

    b2Body* body = m_world.CreateBody(&bodyDefinition);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(halfWidth, halfHeight);

    b2FixtureDef fixtureDefinition;
    fixtureDefinition.shape = &boxShape;
    fixtureDefinition.friction = friction;
    fixtureDefinition.density = 0.0f;
    fixtureDefinition.restitution = 0.0f;

    body->CreateFixture(&fixtureDefinition);
    return body;
}

b2Body* PhysicsWorld::createTriangleRamp(
    float centerX, float centerY,
    float baseWidth, float rampHeight,
    bool slopesUpToRight,
    float friction
) {
    b2BodyDef bodyDefinition;
    bodyDefinition.type = b2_staticBody;
    bodyDefinition.position = b2Vec2(pixelsToMeters(centerX), pixelsToMeters(centerY));

    b2Body* body = m_world.CreateBody(&bodyDefinition);

    const float halfBase = 0.5f * pixelsToMeters(baseWidth);
    const float height = pixelsToMeters(rampHeight);

    b2Vec2 triangleVertices[3];

    if (slopesUpToRight) {
        triangleVertices[0] = b2Vec2(-halfBase, 0.0f);
        triangleVertices[1] = b2Vec2(+halfBase, 0.0f);
        triangleVertices[2] = b2Vec2(+halfBase, -height);
    } else {
        triangleVertices[0] = b2Vec2(+halfBase, 0.0f);
        triangleVertices[1] = b2Vec2(-halfBase, 0.0f);
        triangleVertices[2] = b2Vec2(-halfBase, -height);
    }

    b2PolygonShape triangleShape;
    triangleShape.Set(triangleVertices, 3);

    b2FixtureDef fixtureDefinition;
    fixtureDefinition.shape = &triangleShape;
    fixtureDefinition.friction = friction;
    fixtureDefinition.density = 0.0f;
    fixtureDefinition.restitution = 0.0f;

    body->CreateFixture(&fixtureDefinition);
    return body;
}

void PhysicsWorld::PreSolve(b2Contact* contact, const b2Manifold*) {
    if (!m_playerBody) return;

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    if (bodyA != m_playerBody && bodyB != m_playerBody) {
        return;
    }

    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    b2Vec2 contactNormal = worldManifold.normal;
    if (bodyB == m_playerBody) {
        contactNormal = -contactNormal;
    }

    if (contactNormal.y > GROUND_NORMAL_THRESHOLD) {
        m_isPlayerGrounded = true;
        m_playerGroundNormal = contactNormal;
    }
}

void PhysicsWorld::EndContact(b2Contact* contact) {
    if (!m_playerBody) return;

    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    if (bodyA == m_playerBody || bodyB == m_playerBody) {
        m_isPlayerGrounded = false;
    }
}