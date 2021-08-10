#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent :
    public MoveComponent
{
public:
    InputComponent(class Actor *owner);
    void ProcessInput(const struct InputState &state) override;

	// The maximum forward/angular speeds
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;

	// Keys for angular movement
	int mClockwiseKey;
	int mCounterClockwiseKey;
	// Key for firing bullet
	int mFireKey;

	void SetForwardKey(int key) { m_forwardKey = key; }

private:
	// Keys for forward/back movement
	int m_forwardKey;
	int mBackKey;
};

