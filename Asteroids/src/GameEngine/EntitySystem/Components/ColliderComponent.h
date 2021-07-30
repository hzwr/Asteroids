#pragma once
#include "../Component.h"
#include "math/Math.h"

class ColliderComponent :
    public Component
{
public:
    ColliderComponent(class Actor *owner);

    const Vector3 &GetCenter() const;

    float m_radius;
};

bool Intersect(const ColliderComponent &a, const ColliderComponent &b);
