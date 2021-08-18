#pragma once
#include "Actor.h"
#include "GameEngine/InputSystem/InputSystem.h"
#include <memory>

class ThirdPersonActor :
    public Actor
{
public:
    ThirdPersonActor(class Game *game);

    void ActorInput(const InputState &state) override;

private:
    std::unique_ptr<class MoveComponent> m_moveComp = nullptr;
    std::unique_ptr<class ThirdPersonCamera> m_cameraComp = nullptr;
    std::unique_ptr<class ModelComponent> m_modelComp = nullptr;
};

