#include "Camera.h"
#include "src/GameEngine/EntitySystem/Components/MoveComponent.h"
#include "Game.h"
#include "Renderer.h"



Camera::Camera(Game *game)
	:Actor(game)
{
	m_moveComp = new MoveComponent(this);
}

void Camera::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	// Compute new camera from this actor
	Vector3 cameraPos = GetPosition();
	Vector3 target = GetPosition() + GetForward() * 100.0f;
	Vector3 up = Vector3::UnitZ;

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	GetGame()->GetRenderer()->SetViewMatrix(view);

}

void Camera::ActorInput(const uint8_t *keys)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 300.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 300.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		angularSpeed -= Math::TwoPi;
	}
	if (keys[SDL_SCANCODE_D])
	{
		angularSpeed += Math::TwoPi;
	}

	m_moveComp->SetForwardSpeed(forwardSpeed);
	m_moveComp->SetAngularSpeed(angularSpeed);

}
