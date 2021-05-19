#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor(Game *game)
	:mState(ActorState::EActive)
	,mPosition(Vector2::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
	,mGame(game)
{
	mGame->AddActor(this);

}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	// Delete components
	while(!mComponents.empty())
	{
		delete mComponents.back(); // ~Component calls RemoveComponent, remove itself from mComponents
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == ActorState::EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
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
	auto iter = mComponents.begin();
	for ( ; iter != mComponents.end(); ++iter)
	{
		if (myOrder < (*iter)->mUpdateOrder)
		{
			break;
		}
	}
	mComponents.insert(iter, component);

}

void Actor::RemoveComponent(Component *component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

void Actor::ProcessInput(const uint8_t *keyState)
{
	if (mState == ActorState::EActive)
	{
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}
		ActorInput(keyState); // Actor specific input
	}
}

void Actor::ActorInput(const uint8_t *keyState)
{
}
