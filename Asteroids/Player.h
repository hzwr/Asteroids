#pragma once
#include "Actor.h"
class Player :
    public Actor
{
public:
    Player(class Game *game);
    void UpdateActor(float deltaTime) override;

private:

};

