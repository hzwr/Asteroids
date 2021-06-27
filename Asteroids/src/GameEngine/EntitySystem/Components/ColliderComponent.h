#pragma once
#include "../Component.h"
#include "../../../Math.h"

class ColliderComponent :
    public Component
{
public:
    ColliderComponent(class Actor *owner);

    const Vector2 &GetCenter() const;

    float mRadius;
};

bool Intersect(const ColliderComponent &a, const ColliderComponent &b);
