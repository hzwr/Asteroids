#include "ColliderComponent.h"
#include "../Actor.h"


ColliderComponent::ColliderComponent(Actor *owner)
    :Component(owner)
    ,mRadius(0.0f)
{
}

const Vector2 &ColliderComponent::GetCenter() const
{
    return mOwner->GetPosition();
}

bool Intersect(const ColliderComponent &a, const ColliderComponent &b)
{
    // Calculate distance squared
    Vector2 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();

    // Calculate sum of radii squared
    float radiiSq = a.mRadius + b.mRadius;
    radiiSq *= radiiSq;

    return distSq <= radiiSq;
}