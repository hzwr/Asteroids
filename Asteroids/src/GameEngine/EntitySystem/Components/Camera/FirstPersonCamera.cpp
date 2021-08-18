#include "FirstPersonCamera.h"
#include "GameEngine/EntitySystem/Actor.h"

FirstPersonCamera::FirstPersonCamera(Actor *owner)
	:CameraComponent(owner)
	, m_pitchSpeed(0.0f)
	, m_maxPitch(Math::Pi / 3.0f)
	, m_pitch(0.0f)
{
}

void FirstPersonCamera::Update(float deltaTime)
{
	// Call parent update (doesn't do anything right now)
	CameraComponent::Update(deltaTime);

	// Camera position is owner position
	Vector3 cameraPos = m_owner->GetPosition();

	// Update pitch based on pitch speed
	m_pitch += m_pitchSpeed * deltaTime;
	// Clamp pitch to [-max, +max]
	m_pitch = Math::Clamp(m_pitch, -m_maxPitch, m_maxPitch);
	// Make a quaternion representing pitch rotation,
	// which is about owner's right vector
	Quaternion q(m_owner->GetRight(), m_pitch);

	// Rotate owner forward by pitch quaternion
	Vector3 viewForward = Vector3::Transform(
		m_owner->GetForward(), q);
	// Target position 100 units in front of view forward
	Vector3 target = cameraPos + viewForward * 100.0f;

	// Also rotate up by pitch quaternion
	Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

	// Create look at matrix, set as view
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}
