#pragma once
#include "../Component.h"
#include "math/Math.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor *owner, int updateOrder = 10);
	void Update(float deltaTime) override;



	Vector3 mVelocityVector; 

	float GetAngularSpeed() const { return m_angularSpeed; }
	float GetForwardSpeed() const { return m_forwardSpeed; }
	float GetStrafeSpeed() const { return m_strafeSpeed; }
	void SetAngularSpeed(float speed) { m_angularSpeed = speed; }
	void SetForwardSpeed(float speed) { m_forwardSpeed = speed; }
	void SetStrafeSpeed(float speed) { m_strafeSpeed = speed; }
private:
	float m_angularSpeed;
	float m_forwardSpeed;
	float m_strafeSpeed;
};

