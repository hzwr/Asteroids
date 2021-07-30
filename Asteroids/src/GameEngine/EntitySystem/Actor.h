#pragma once
#include <vector>
#include "math/Math.h"
#include <SDL/SDL.h>

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
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, m_rotation); }
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, m_rotation); }

	// Input
	void ProcessInput(const uint8_t *keyState); // Process input on all components and call actor-specific input
	virtual void ActorInput(const uint8_t *keyState); // Actor-specific input code
	
	// Getters/setters
	ActorState GetState() const { return m_state; }
	void SetState(ActorState state) { m_state = state; }
	const Vector3 &GetPosition() const { return m_position; }
	void SetPosition(const Vector3 &pos) { SDL_Log("x: %f",m_position.x); SDL_Log("y: %f", m_position.y); SDL_Log("z: %f", m_position.z);  m_position = pos; m_recomputeWorldTransform = true; }
	float GetScale() const { return m_scale; }
	void SetScale(float scale) { m_scale = scale;  m_recomputeWorldTransform = true; }
	Quaternion GetRotation() const { return m_rotation; }
	void SetRotation(Quaternion rotation) { m_rotation = rotation;  m_recomputeWorldTransform = true; }

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return m_worldTransform; }

private:
	ActorState m_state;
	float m_scale;
	Quaternion m_rotation; // Counter-clockwise, represents the direction the object faces
	Vector3 m_position;
	Matrix4 m_worldTransform;
	bool m_recomputeWorldTransform = true;
	std::vector<class Component *> m_components;
	class Game *mGame;

};

