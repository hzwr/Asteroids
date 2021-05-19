#include "InputComponent.h"
#include "Bullet.h"

InputComponent::InputComponent(class Actor *owner)
	:MoveComponent(owner)
	, mForwardKey(0)
	, mBackKey(0)
	, mClockwiseKey(0)
	, mCounterClockwiseKey(0)
	, mFireKey(0)
	, mMaxAngularSpeed(0.0f)
	, mMaxForwardSpeed(0.0f)
{

}

void InputComponent::ProcessInput(const uint8_t *keyState)
{
	if (keyState[mForwardKey])
	{
		// Thurst 
		// Update velocity
		// TODO: velocity should be updated using acceleration * time
		mVelocityVector += mOwner->GetForward() * 10;
	}
	if (keyState[mBackKey])
	{
		
	}

	if (keyState[mFireKey])
	{
		Bullet *bullet = new Bullet(mOwner->GetGame(), mOwner->mRotation);
		bullet->mPosition = mOwner->mPosition;	// Instantiate a bullet at the ship's postition
	}


	// Calculate angular speed for MoveComponent
	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	mAngularSpeed = angularSpeed;
}
