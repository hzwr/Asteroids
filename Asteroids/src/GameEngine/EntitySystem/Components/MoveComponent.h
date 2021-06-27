#pragma once
#include "../Component.h"
#include "../../../Math.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor *owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float mAngularSpeed;
	float mForwardSpeed;

	Vector2 mVelocityVector; 
};

