#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "math/Math.h"

class CameraComponent : public Component
{
public:
	CameraComponent(class Actor *owner, int updateOrder = 200);

protected:
	void SetViewMatrix(Matrix4 &view);
};