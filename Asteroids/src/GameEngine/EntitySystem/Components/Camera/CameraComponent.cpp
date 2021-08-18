#include "GameEngine/EntitySystem/Actor.h"
#include "CameraComponent.h"
#include "Renderer.h"
#include "Game.h"

CameraComponent::CameraComponent(Actor *owner, int updateOrder)
	:Component(owner, updateOrder)
{
}

void CameraComponent::SetViewMatrix(Matrix4 &view)
{
	m_owner->GetGame()->GetRenderer()->SetViewMatrix(view);
}
