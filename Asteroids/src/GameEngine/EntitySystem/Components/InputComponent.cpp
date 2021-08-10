#include "InputComponent.h"
#include "../../../Bullet.h"

InputComponent::InputComponent(class Actor *owner)
	:MoveComponent(owner)
	, m_forwardKey(0)
	, mBackKey(0)
	, mClockwiseKey(0)
	, mCounterClockwiseKey(0)
	, mFireKey(0)
	, mMaxAngularSpeed(0.0f)
	, mMaxForwardSpeed(0.0f)
{

}

void InputComponent::ProcessInput(const struct InputState &state)
{
	if (state.keyboard.GetKeyValue(SDL_SCANCODE_W))
	{
		// Thurst 
		// Update velocity
		// TODO: velocity should be updated using acceleration * time
		mVelocityVector += m_owner->GetForward() * 10;
	}

	//// Calculate angular speed for MoveComponent
	//float angularSpeed = 0.0f;
	//if (keyState[mClockwiseKey])
	//{
	//	angularSpeed -= mMaxAngularSpeed;
	//}
	//if (keyState[mCounterClockwiseKey])
	//{
	//	angularSpeed += mMaxAngularSpeed;
	//}
	//SetAngularSpeed(angularSpeed);
}
