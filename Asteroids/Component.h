#pragma once
#include <cstdint>

class Component
{
public:
	// Lower update order means higher priority 
	Component(class Actor *owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime);
	virtual void ProcessInput(const uint8_t *keyState);
	
	int mUpdateOrder;

protected:
	class Actor *mOwner;
};

