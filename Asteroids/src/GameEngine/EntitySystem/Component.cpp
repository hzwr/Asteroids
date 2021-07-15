#include "Component.h"
#include "Actor.h"

Component::Component(Actor *owner, int updateOrder)
	:m_owner(owner)
	,mUpdateOrder(updateOrder)
{
	m_owner->AddComponent(this);
}

Component::~Component()
{
	m_owner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}

void Component::ProcessInput(const uint8_t *keyState)
{
}
