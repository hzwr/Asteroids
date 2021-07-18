#include "MoveComponent.h"
#include "../Actor.h"
#include <iostream>
#include <string>

MoveComponent::MoveComponent(Actor *owner, int updateOrder)
	:Component(owner, updateOrder)
	,mAngularSpeed(0.0f)
	,mForwardSpeed(1.0f)
	,mVelocityVector(Vector3(0.0f, 0.0f, 0.0f))
{
}

void MoveComponent::Update(float deltaTime)
{
	// Update rotation
	if (!Math::NearZero(mAngularSpeed))
	{
		Quaternion rot = m_owner->GetRotation();
		float angle = mAngularSpeed * deltaTime;
		Quaternion inc(Vector3::UnitZ, angle);	
		rot = Quaternion::Concatenate(rot, inc); 
		m_owner->SetRotation(rot);
		/*std::cout << std::to_string(mOwner->mRotation) << std::endl;*/
	}

	// Update position
	if (!Math::NearZero(mForwardSpeed))	// forward and velocity vector always face the same direction
	{
		Vector3 pos = m_owner->GetPosition();
		pos += m_owner->GetForward() * mForwardSpeed * deltaTime;
		
		//
		//// Screen wrapping
		//if (pos.x < -960.0f)
		//{
		//	pos.x = 958.0f;
		//}
		//else if (pos.x > 960.0f)
		//{
		//	pos.x = -958.0f;
		//}

		//if (pos.y < -540.0f)
		//{
		//	pos.y = 538.0f;
		//}
		//else if (pos.y > 540.0f)
		//{
		//	pos.y = -538.0f;
		//}
		//
		m_owner->SetPosition(pos);
	}
}
