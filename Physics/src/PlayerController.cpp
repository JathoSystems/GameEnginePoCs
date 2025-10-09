#include "PlayerController.h"
#include <cmath>

namespace {
    constexpr float BRAKE_STRENGTH = 8.0f;
    constexpr float SPEED_CAP_MULTIPLIER = 1.8f;
    constexpr float MIN_DELTA_TIME = 1e-4f;
    
    constexpr float SLOPE_SPEED_REDUCTION = 0.05f;
    constexpr float CLIMB_PENALTY_BASE = 0.75f;
    constexpr float CLIMB_PENALTY_OFFSET = 0.1f;
    constexpr float MIN_CLIMB_SCALE = 0.4f;
    constexpr float MAX_CLIMB_SCALE = 0.85f;
}

void PlayerController::handleInput(const SDL_Event& event) {
    if (event.type != SDL_EVENT_KEY_DOWN && event.type != SDL_EVENT_KEY_UP) {
        return;
    }

    const bool isKeyPressed = (event.type == SDL_EVENT_KEY_DOWN);

    switch (event.key.key) {
        case SDLK_A: 
            m_isMovingLeft = isKeyPressed; 
            break;
        case SDLK_D: 
            m_isMovingRight = isKeyPressed; 
            break;
        case SDLK_W: 
            m_wantsToJump = isKeyPressed; 
            break;
        case SDLK_S: 
            m_isBraking = isKeyPressed; 
            break;
        default: 
            break;
    }
}

void PlayerController::update(PhysicsWorld& physicsWorld, float deltaTime) {
    if (!m_playerBody) return;

    m_playerBody->SetFixedRotation(true);

    b2Vec2 currentVelocity = m_playerBody->GetLinearVelocity();

    const bool isGrounded = physicsWorld.isPlayerGrounded();
    const b2Vec2 groundNormal = isGrounded 
        ? physicsWorld.getPlayerGroundNormal() 
        : b2Vec2(0.0f, 1.0f); // Default upward normal when airborne

    const b2Vec2 groundTangent(groundNormal.y, -groundNormal.x);

    const float moveDirection =
        (m_isMovingRight ? 1.0f : 0.0f) + 
        (m_isMovingLeft ? -1.0f : 0.0f);

    const float speedModifier = calculateSlopeSpeedPenalty(groundNormal);
    const float targetSpeed = horizontalSpeed * speedModifier * moveDirection;

    const float currentSpeedAlongSlope = b2Dot(currentVelocity, groundTangent);
    const float speedDifference = targetSpeed - currentSpeedAlongSlope;
    float desiredAcceleration = speedDifference / b2Max(deltaTime, MIN_DELTA_TIME);

    if (isGrounded && moveDirection != 0.0f) {
        const float slopeAngle = acosf(b2Clamp(b2Dot(groundNormal, b2Vec2(0.0f, 1.0f)), -1.0f, 1.0f));
        const float climbPenalty = calculateClimbingAccelerationPenalty(
            groundNormal, groundTangent, moveDirection, slopeAngle
        );
        desiredAcceleration *= climbPenalty;
    }

    desiredAcceleration = b2Clamp(desiredAcceleration, -maxAcceleration, maxAcceleration);

    currentVelocity += desiredAcceleration * deltaTime * groundTangent;

    if (m_isBraking) {
        const float tangentSpeed = b2Dot(currentVelocity, groundTangent);
        currentVelocity -= tangentSpeed * BRAKE_STRENGTH * deltaTime * groundTangent;
    }

    if (isGrounded && m_wantsToJump) {
        currentVelocity.y = -jumpStrength;
    }

    const float speedAlongSlope = b2Dot(currentVelocity, groundTangent);
    const float speedCap = horizontalSpeed * SPEED_CAP_MULTIPLIER;
    
    if (speedAlongSlope > speedCap) {
        currentVelocity += (speedCap - speedAlongSlope) * groundTangent;
    } else if (speedAlongSlope < -speedCap) {
        currentVelocity += (-speedCap - speedAlongSlope) * groundTangent;
    }

    m_playerBody->SetLinearVelocity(currentVelocity);
}

float PlayerController::calculateSlopeSpeedPenalty(const b2Vec2& groundNormal) const {
    const float dotProduct = b2Dot(groundNormal, b2Vec2(0.0f, 1.0f));
    const float slopeAngle = acosf(b2Clamp(dotProduct, -1.0f, 1.0f));
    
    const float cosineSquared = cosf(slopeAngle) * cosf(slopeAngle);
    
    return b2Max(0.0f, cosineSquared - SLOPE_SPEED_REDUCTION);
}

float PlayerController::calculateClimbingAccelerationPenalty(
    const b2Vec2& groundNormal,
    const b2Vec2& tangent,
    float moveDirection,
    float slopeAngle
) const {
    const bool isMovingUphill =
        (moveDirection > 0.0f && tangent.y < 0.0f) || 
        (moveDirection < 0.0f && tangent.y > 0.0f);
    
    if (!isMovingUphill) {
        return 1.0f;
    }
    
    const float climbScale = CLIMB_PENALTY_BASE * cosf(slopeAngle) + CLIMB_PENALTY_OFFSET;
    return b2Clamp(climbScale, MIN_CLIMB_SCALE, MAX_CLIMB_SCALE);
}