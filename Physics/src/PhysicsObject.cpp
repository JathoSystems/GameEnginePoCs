#include "PhysicsObject.h"
#include <cmath>

namespace {
    void renderRotatedRectangle(
        SDL_Renderer* renderer,
        float centerX, float centerY,
        float width, float height,
        float rotationRadians,
        Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha
    ) {
        SDL_Vertex vertices[4]{};
        const float halfWidth = width * 0.5f;
        const float halfHeight = height * 0.5f;
        const float cosAngle = cosf(rotationRadians);
        const float sinAngle = sinf(rotationRadians);

        auto setVertex = [&](int index, float localX, float localY) {
            vertices[index].position.x = centerX + (localX * cosAngle - localY * sinAngle);
            vertices[index].position.y = centerY + (localX * sinAngle + localY * cosAngle);
            vertices[index].color = SDL_FColor{red/255.f, green/255.f, blue/255.f, alpha/255.f};
        };

        setVertex(0, -halfWidth, -halfHeight);
        setVertex(1, +halfWidth, -halfHeight);
        setVertex(2, +halfWidth, +halfHeight);
        setVertex(3, -halfWidth, +halfHeight);

        int indices[6]{0, 1, 2, 0, 2, 3};
        SDL_RenderGeometry(renderer, nullptr, vertices, 4, indices, 6);
    }
}

PhysicsObject::PhysicsObject(
    PhysicsWorld& physicsWorld,
    float topLeftX, float topLeftY,
    float width, float height,
    bool isDynamic
)
    : m_physicsWorld(physicsWorld)
    , m_width(width)
    , m_height(height)
{
    m_physicsBody = m_physicsWorld.createRectangleBody(
        topLeftX, topLeftY,
        width, height,
        isDynamic
    );
}

void PhysicsObject::render(SDL_Renderer* renderer) const {
    b2Vec2 position = m_physicsBody->GetPosition();
    float rotationAngle = m_physicsBody->GetAngle();

    const float centerX = position.x * PhysicsWorld::PIXELS_PER_METER;
    const float centerY = position.y * PhysicsWorld::PIXELS_PER_METER;

    renderRotatedRectangle(
        renderer,
        centerX, centerY,
        m_width, m_height,
        rotationAngle,
        255, 0, 0, 255
    );
}

void PhysicsObject::resetPosition(float topLeftX, float topLeftY) {
    const float halfWidth = 0.5f * m_width / PhysicsWorld::PIXELS_PER_METER;
    const float halfHeight = 0.5f * m_height / PhysicsWorld::PIXELS_PER_METER;

    const float centerX = (topLeftX / PhysicsWorld::PIXELS_PER_METER) + halfWidth;
    const float centerY = (topLeftY / PhysicsWorld::PIXELS_PER_METER) + halfHeight;

    m_physicsBody->SetTransform(b2Vec2(centerX, centerY), 0.0f);
    m_physicsBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    m_physicsBody->SetAngularVelocity(0.0f);
    m_physicsBody->SetAwake(true);
}