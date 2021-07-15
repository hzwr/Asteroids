#include "ColliderComponent.h"
#include "../Actor.h"


ColliderComponent::ColliderComponent(Actor *owner)
    :Component(owner)
    ,m_radius(0.0f)
{
}

const Vector3 &ColliderComponent::GetCenter() const
{
    return m_owner->GetPosition();
}

bool Intersect(const ColliderComponent &a, const ColliderComponent &b)
{
    // Calculate distance squared
    Vector3 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();

    // Calculate sum of radii squared
    float radiiSq = a.m_radius + b.m_radius;
    radiiSq *= radiiSq;

    return distSq <= radiiSq;
}