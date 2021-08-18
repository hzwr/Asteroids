#include "ThirdPersonActor.h"
#include "Components/ModelComponent.h"
#include "Components/MoveComponent.h"
#include "Components/Camera/ThirdPersonCamera.h"
#include "Game.h"
#include "Renderer.h"

ThirdPersonActor::ThirdPersonActor(Game *game)
	:Actor(game)
{
	m_modelComp = std::make_unique<ModelComponent>(this);
	m_modelComp->SetModel(game->GetRenderer()->GetModel("Assets/plane/plane.obj"));
	//Quaternion q = Quaternion(Vector3::UnitY, -Math::PiOver2);
	//SetRotation(q);
	SetPosition(Vector3(10.0f, 0.0f, 10.0f));

	m_moveComp = std::make_unique<MoveComponent>(this);
	m_cameraComp = std::make_unique<ThirdPersonCamera>(this);
	m_cameraComp->Reset();
}

void ThirdPersonActor::ActorInput(const InputState &state)
{
	float forwardSpeed = 0.0f;
	//float angularSpeed = 0.0f;
	float strafeSpeed = 0.0f;

	// wasd movement
	if (state.keyboard.GetKeyValue(SDL_SCANCODE_W))
	{
		forwardSpeed += 30.0f;
	}
	if (state.keyboard.GetKeyValue(SDL_SCANCODE_S))
	{
		forwardSpeed -= 30.0f;
	}
	if (state.keyboard.GetKeyValue(SDL_SCANCODE_A))
	{
		//angularSpeed -= Math::TwoPi;
		strafeSpeed -= 30.0f;

	}
	if (state.keyboard.GetKeyValue(SDL_SCANCODE_D))
	{
		//angularSpeed += Math::TwoPi;
		strafeSpeed += 30.0f;
	}

	m_moveComp->SetForwardSpeed(forwardSpeed);
	m_moveComp->SetStrafeSpeed(strafeSpeed);
	//m_moveComp->SetAngularSpeed(angularSpeed);
}
