#pragma once
#include <vector>
#include "../../Math.h"

enum class ActorState
{
	EActive,
	EPaused,
	EDead
};

class Actor
{
public:

	Actor(class Game *game);
	virtual ~Actor();
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime); // Actor-specific update

	void AddComponent(class Component *component);
	void RemoveComponent(class Component *component);

	class Game *GetGame() const { return mGame; }
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	// Input
	void ProcessInput(const uint8_t *keyState); // Process input on all components and call actor-specific input
	virtual void ActorInput(const uint8_t *keyState); // Actor-specific input code

	ActorState mState;
	float mScale;
	float mRotation; // Counter-clockwise, represents the direction the object faces
	Vector2 mPosition;

private:
	std::vector<class Component *> mComponents;
	class Game *mGame;

};

