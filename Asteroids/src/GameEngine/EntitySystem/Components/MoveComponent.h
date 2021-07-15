#pragma once
#include "../Component.h"
#include "src/Vendor/Math.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor *owner, int updateOrder = 10);
	void Update(float deltaTime) override;



	Vector3 mVelocityVector; 

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
private:
	float mAngularSpeed;
	float mForwardSpeed;
};

