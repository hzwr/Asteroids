#pragma once
#include "GameEngine\EntitySystem\Actor.h"

class Player :
    public Actor
{
public:
    Player(class Game *game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const InputState &state) override;
    class ColliderComponent *GetCollider() { return mCollider; }

private:
    float mWeaponCooldown;
    class ColliderComponent *mCollider;

};

