#pragma once
#include <box2d/box2d.h>

class PhysicsWorld : public b2ContactListener {
public:
    static constexpr float PIXELS_PER_METER = 100.0f;

    PhysicsWorld(float gravityX = 0.0f, float gravityY = 9.81f);
    ~PhysicsWorld() = default;

    void stepSimulation(float deltaTime);

    b2Body* createRectangleBody(
        float topLeftX, float topLeftY,
        float width, float height,
        bool isDynamic = true,
        float density = 1.0f,
        float friction = 0.9f,
        float bounciness = 0.0f
    );

    b2Body* createRotatedRamp(
        float centerX, float centerY,
        float width, float height,
        float rotationDegrees,
        float friction = 0.9f
    );

    b2Body* createTriangleRamp(
        float centerX, float centerY,
        float baseWidth, float rampHeight,
        bool slopesUpToRight,
        float friction = 0.9f
    );

    b2World& getWorld() { return m_world; }

    void setPlayerBody(b2Body* playerBody) { m_playerBody = playerBody; }

    bool isPlayerGrounded() const { return m_isPlayerGrounded; }

    b2Vec2 getPlayerGroundNormal() const { return m_playerGroundNormal; }

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
    void EndContact(b2Contact* contact) override;

private:
    b2World m_world;

    static constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
    static constexpr int VELOCITY_ITERATIONS = 8;
    static constexpr int POSITION_ITERATIONS = 3;

    float m_timeAccumulator = 0.0f;

    b2Body* m_playerBody = nullptr;
    bool m_isPlayerGrounded = false;
    b2Vec2 m_playerGroundNormal = b2Vec2(0.0f, 1.0f);

    static float pixelsToMeters(float pixels) { return pixels / PIXELS_PER_METER; }
    static float metersToPixels(float meters) { return meters * PIXELS_PER_METER; }
};