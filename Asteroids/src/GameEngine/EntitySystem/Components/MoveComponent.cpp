#include "MoveComponent.h"
#include "../Actor.h"
#include <iostream>
#include <string>

MoveComponent::MoveComponent(Actor *owner, int updateOrder)
	:Component(owner, updateOrder)
	,mAngularSpeed(0.0f)
	,mForwardSpeed(1.0f)
	,mVelocityVector( Vector2(0.0f, 0.0f))
{
}

void MoveComponent::Update(float deltaTime)
{
	// Update rotation
	if (!Math::NearZero(mAngularSpeed))
	{
		float rotation = mOwner->GetRotation();
		rotation += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rotation);
		/*std::cout << std::to_string(mOwner->mRotation) << std::endl;*/
	}

	// Update position
	if (!Math::NearZero(mVelocityVector.x * mVelocityVector.x + mVelocityVector.y * mVelocityVector.y))
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mVelocityVector * mForwardSpeed * deltaTime;
		
		
		// Screen wrapping
		if (pos.x < 0.0f)
		{
			pos.x = 1918.0f;
		}
		else if (pos.x > 1920.0f)
		{
			pos.x = 2.0f;
		}

		if (pos.y < 0.0f)
		{
			pos.y = 1078.0f;
		}
		else if (pos.y > 1080.0f)
		{
			pos.y = 2.0f;
		}
		
		mOwner->SetPosition(pos);
	}
}
