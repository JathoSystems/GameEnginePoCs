//
// Created by jusra on 2-10-2025.
//

#ifndef UIELEMENT_ANIMATION_H
#define UIELEMENT_ANIMATION_H
#include <map>
#include <memory>

#include "AnimationType.h"
#include "Keyframe.h"
#include "../Components/UIElement.h"
#include "../Utils/Position.h"


class Animation : public UIElement {
private:
    float _currentTime;
    std::pmr::map<int, Keyframe> _animation;
    std::unique_ptr<UIElement> _element;
    AnimationType _animationType;
    bool _loop;

public:
    Animation(std::unique_ptr<UIElement> element, AnimationType animationType = AnimationType::LERP,
              bool autoLoop = true);

    void addKeyframe(int time, Keyframe keyframe);

    void render(SDL_Renderer *renderer) override;

    void setLoop(bool loop);

    Keyframe *findNextKeyframeWithProperty(int currentTime, bool (Keyframe::*hasProperty)() const);

    void reset();

    void update(float deltaTime) override;
};


#endif //UIELEMENT_ANIMATION_H
