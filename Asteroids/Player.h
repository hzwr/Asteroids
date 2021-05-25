#pragma once
#include "Actor.h"

class Player :
    public Actor
{
public:
    Player(class Game *game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t *keyState) override;
    class ColliderComponent *GetCollider() { return mCollider; }

private:
    float mWeaponCooldown;
    class ColliderComponent *mCollider;

};

