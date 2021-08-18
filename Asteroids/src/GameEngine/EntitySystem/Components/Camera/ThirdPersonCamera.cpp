#include "ThirdPersonCamera.h"
#include "GameEngine/EntitySystem/Actor.h"
#include <iostream>

ThirdPersonCamera::ThirdPersonCamera(Actor *owner)
	:CameraComponent(owner)
	, mHorzDist(60.0f)
	, mVertDist(18.0f)
	, mTargetDist(5.0f)
	, mSpringConstant(64.0f)
{
}

void ThirdPersonCamera::Update(float deltaTime)
{
	//CameraComponent::Update(deltaTime);
	// Compute dampening from spring constant
	float dampening = 2.0f * Math::Sqrt(mSpringConstant);
	// Compute ideal position
	Vector3 idealPos = ComputeCameraPos();
	// Compute difference between actual and ideal
	Vector3 diff = mActualPos - idealPos;
	// Compute acceleration of spring
	Vector3 acel = -mSpringConstant * diff -
		dampening * mVelocity;
	// Update velocity
	mVelocity += acel * deltaTime;
	// Update actual camera position
	mActualPos += mVelocity * deltaTime;
	// Target is target dist in front of owning actor
	Vector3 target = m_owner->GetPosition() +
		m_owner->GetForward() * mTargetDist;
	// Use actual position here, not ideal

	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target,
		Vector3::UnitZ);
	SetViewMatrix(view);
}

void ThirdPersonCamera::Reset()
{
	// Set actual position to ideal
	mActualPos = ComputeCameraPos();
	// Zero velocity
	mVelocity = Vector3::Zero;
	// Compute target and view
	Vector3 target = m_owner->GetPosition();
	//	m_owner->GetForward() * mTargetDist;
	// Use actual position here, not ideal
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target,
		Vector3::UnitZ);
	SetViewMatrix(view);
}

Vector3 ThirdPersonCamera::ComputeCameraPos() const
{
	// Set camera position behind and above owner
	Vector3 cameraPos = m_owner->GetPosition();
	cameraPos -= m_owner->GetForward() * mHorzDist;
	cameraPos += Vector3::UnitZ * mVertDist;
	std::cout << "cameraPos " << cameraPos.x << ", " << cameraPos.y <<", " <<cameraPos.z<< std::endl;
	return cameraPos;
}
