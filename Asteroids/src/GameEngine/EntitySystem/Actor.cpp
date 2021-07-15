#include "Actor.h"
#include "../../Game.h"
#include "Component.h"

Actor::Actor(Game *game)
	:m_state(ActorState::EActive)
	,m_position(Vector3::Zero)
	,m_scale(1.0f)
	,m_rotation(Quaternion::Identity)
	,mGame(game)
{
	mGame->AddActor(this);
	m_recomputeWorldTransform = true;
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	// Delete components
	while(!m_components.empty())
	{
		delete m_components.back(); // ~Component calls RemoveComponent, remove itself from mComponents
	}
}

void Actor::Update(float deltaTime)
{
	if (m_state == ActorState::EActive)
	{
		ComputeWorldTransform();
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
		ComputeWorldTransform();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : m_components)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component *component)
{
	// Add the component according to the update order
	// Find the first component with a larger update order, and insert before that component
	int myOrder = component->mUpdateOrder;
	auto iter = m_components.begin();
	for ( ; iter != m_components.end(); ++iter)
	{
		if (myOrder < (*iter)->mUpdateOrder)
		{
			break;
		}
	}
	m_components.insert(iter, component);

}

void Actor::RemoveComponent(Component *component)
{
	auto iter = std::find(m_components.begin(), m_components.end(), component);
	if (iter != m_components.end())
	{
		m_components.erase(iter);
	}
}

void Actor::ProcessInput(const uint8_t *keyState)
{
	if (m_state == ActorState::EActive)
	{
		for (auto comp : m_components)
		{
			comp->ProcessInput(keyState);
		}
		ActorInput(keyState); // Actor specific input
	}
}

void Actor::ActorInput(const uint8_t *keyState)
{
}

void Actor::ComputeWorldTransform()
{
	if (m_recomputeWorldTransform)
	{
		m_recomputeWorldTransform = false;
		m_worldTransform = Matrix4::CreateScale(m_scale);
		m_worldTransform *= Matrix4::CreateFromQuaternion(m_rotation);
		m_worldTransform *= Matrix4::CreateTranslation(m_position);
	}

	for (auto component : m_components)
	{
		component->OnUpdateWorldTransform();
	}
}
