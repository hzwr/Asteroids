#include "FPSActor.h"
#include "GameEngine/EntitySystem/Components/MoveComponent.h"
#include "GameEngine/EntitySystem/Components/Camera/FirstPersonCamera.h"

FPSActor::FPSActor(Game *game)
	:Actor(game)
{
	m_moveComp = new MoveComponent(this);
	m_cameraComp = new FirstPersonCamera(this);
}

void FPSActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
}

void FPSActor::ActorInput(const InputState &state)
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


	// Mouse movement
	const int maxMouseSpeed = 500;
	float angularSpeed = 0.0f;
	const float maxAngularSpeed = Math::Pi * 8;
	int x = state.mouse.GetPosition().x; // relative pos, set this in game.cpp
	int y = state.mouse.GetPosition().y; // relative pos, set this in game.cpp
	if (x != 0)
	{
		angularSpeed = static_cast<float>(x) / maxMouseSpeed;
		angularSpeed *= maxAngularSpeed;
	}
	m_moveComp->SetAngularSpeed(angularSpeed);


	// Update camera pitch speed based on mouse movement
	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	m_cameraComp->SetPitchSpeed(pitchSpeed);

	
}
