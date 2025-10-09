#pragma once
#include <SDL3/SDL.h>
#include <box2d/box2d.h>
#include "Physics.h"

class PlayerController {
public:
    PlayerController() = default;

    void setBody(b2Body* playerBody) { m_playerBody = playerBody; }

    void handleInput(const SDL_Event& event);

    void update(PhysicsWorld& physicsWorld, float deltaTime);

    float horizontalSpeed = 6.0f;
    float jumpStrength = 7.0f;
    float maxAcceleration = 70.0f;

private:
    b2Body* m_playerBody = nullptr;

    bool m_isMovingLeft = false;
    bool m_isMovingRight = false;
    bool m_wantsToJump = false;
    bool m_isBraking = false;

    float calculateSlopeSpeedPenalty(const b2Vec2& groundNormal) const;

    float calculateClimbingAccelerationPenalty(
        const b2Vec2& groundNormal,
        const b2Vec2& tangent,
        float moveDirection,
        float slopeAngle
    ) const;
};