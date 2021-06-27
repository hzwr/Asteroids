#pragma once
#include "GameEngine\EntitySystem\Actor.h"

class Asteroid :
    public Actor
{
public:
    Asteroid(class Game *game);
    ~Asteroid();

    class ColliderComponent *GetCollider() { return mCollider; }

    
private:
    class ColliderComponent *mCollider;
};

