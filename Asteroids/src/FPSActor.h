#pragma once
#include "GameEngine/EntitySystem/Actor.h"
#include "GameEngine/InputSystem/InputSystem.h"

class FPSActor :
    public Actor
{
public:
    FPSActor(class Game *game);

    void UpdateActor(float deltaTime) override;
    void ActorInput(const InputState &state) override;

private:
    class MoveComponent *m_moveComp;
    class FirstPersonCamera *m_cameraComp;

};

