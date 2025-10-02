//
// Created by jusra on 2-10-2025.
//

#include "../../include/Animation/Animation.h"
#include <cmath>
#include <algorithm>
#include <iostream>

void lerp(UIElement* element, Keyframe* k1, Keyframe* k2, float t) {
    if (!element || !k1 || !k2) {
        std::cerr << "lerp: element or keyframe is null!" << std::endl;
        return;
    }

    // Position interpolatie
    if (k1->getPosition() && k2->getPosition()) {
        float x = k1->getPosition()->getX() + t * (k2->getPosition()->getX() - k1->getPosition()->getX());
        float y = k1->getPosition()->getY() + t * (k2->getPosition()->getY() - k1->getPosition()->getY());
        element->setPosition((int)x, (int)y);
    }

    // Scale interpolatie
    if (k1->getScale() && k2->getScale()) {
        float scale1 = k1->getScale()->getScale();
        float scale2 = k2->getScale()->getScale();
        float scale = scale1 + t * (scale2 - scale1);
        element->setScale(scale);
    }

    // Color interpolatie
    if (k1->getColor() && k2->getColor()) {
        int r = k1->getColor()->getR() + t * (k2->getColor()->getR() - k1->getColor()->getR());
        int g = k1->getColor()->getG() + t * (k2->getColor()->getG() - k1->getColor()->getG());
        int b = k1->getColor()->getB() + t * (k2->getColor()->getB() - k1->getColor()->getB());
        element->setColor(r, g, b);
    }
}

void easeInOut(UIElement* element, Keyframe* k1, Keyframe* k2, float t) {
    t = t * t * (3 - 2 * t);
    lerp(element, k1, k2, t);
}

Animation::Animation(std::unique_ptr<UIElement> element, AnimationType animationType, bool loop)
    : _element(std::move(element)), _animationType(animationType), _loop(loop), _currentTime(0.0f) {
}

void Animation::addKeyframe(int time, Keyframe keyframe) {
    _animation[time] = keyframe;
}

void Animation::render(SDL_Renderer *renderer) {
    _element->render(renderer);
}

void Animation::reset() {
    _currentTime = 0.0f;

    if (!_animation.empty()) {
        Keyframe* k = &(_animation.begin()->second);
        lerp(_element.get(), k, k, 0.0f);
    }
}

void Animation::setLoop(bool loop) {
    _loop = loop;
}

// Helper functie om de volgende keyframe te vinden met een specifieke property
Keyframe* Animation::findNextKeyframeWithProperty(int currentTime, bool (Keyframe::*hasProperty)() const) {
    // Zoek vanaf huidige tijd
    for (auto it = _animation.upper_bound(currentTime); it != _animation.end(); ++it) {
        if ((it->second.*hasProperty)()) {
            return &(it->second);
        }
    }

    // Wrap around als loop enabled is
    if (_loop) {
        for (auto it = _animation.begin(); it != _animation.end(); ++it) {
            if (it->first > currentTime) break;
            if ((it->second.*hasProperty)()) {
                return &(it->second);
            }
        }
    }

    return nullptr;
}

void Animation::update(float deltaTime) {
    _currentTime += deltaTime;
    if (_animation.empty()) return;

    // Auto-loop als enabled
    if (_loop) {
        int lastKeyframeTime = _animation.rbegin()->first;
        if (_currentTime > lastKeyframeTime) {
            _currentTime = fmodf(_currentTime, (float)lastKeyframeTime);
        }
    }

    auto itAfter = _animation.upper_bound((int)_currentTime);

    if (itAfter == _animation.begin()) {
        Keyframe* k = &(_animation.begin()->second);
        lerp(_element.get(), k, k, 0.0f);
        _element->update(deltaTime);
        return;
    }

    auto itBefore = std::prev(itAfter);

    if (itAfter == _animation.end()) {
        Keyframe* k = &(itBefore->second);
        lerp(_element.get(), k, k, 1.0f);
        _element->update(deltaTime);
        return;
    }

    Keyframe* k1 = &(itBefore->second);
    Keyframe* k2 = &(itAfter->second);

    // Als k2 geen property heeft, zoek dan de volgende die het wel heeft
    Keyframe* targetPosition = k2->getPosition() ? k2 : findNextKeyframeWithProperty(itAfter->first, &Keyframe::hasPosition);
    Keyframe* targetScale = k2->getScale() ? k2 : findNextKeyframeWithProperty(itAfter->first, &Keyframe::hasScale);

    float t = (_currentTime - itBefore->first) / float(itAfter->first - itBefore->first);
    t = std::clamp(t, 0.0f, 1.0f);

    Keyframe* targetColor = k2->getColor() ? k2 : findNextKeyframeWithProperty(itAfter->first, &Keyframe::hasColor);

    // Maak tijdelijke keyframe met de juiste targets
    Keyframe effectiveK2;
    if (targetPosition) {
        effectiveK2.setPosition(targetPosition->getPosition()->getX(), targetPosition->getPosition()->getY());
    }
    if (targetScale) {
        effectiveK2.setScale(targetScale->getScale()->getScale());
    }
    if (targetColor) {
        effectiveK2.setColor(targetColor->getColor()->getR(),
                            targetColor->getColor()->getG(),
                            targetColor->getColor()->getB());
    }


    switch (_animationType) {
        case AnimationType::LERP:
            lerp(_element.get(), k1, &effectiveK2, t);
            break;
        case AnimationType::EIEO:
            easeInOut(_element.get(), k1, &effectiveK2, t);
            break;
    }

    _element->update(deltaTime);
}