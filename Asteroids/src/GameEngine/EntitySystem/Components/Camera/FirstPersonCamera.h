#pragma once
#include "CameraComponent.h"

class FirstPersonCamera :
    public CameraComponent
{
public:
    FirstPersonCamera(class Actor *owner);

    void Update(float deltaTime) override;

	float GetPitch() const { return m_pitch; }
	float GetPitchSpeed() const { return m_pitchSpeed; }
	float GetMaxPitch() const { return m_maxPitch; }

	void SetPitchSpeed(float speed) { m_pitchSpeed = speed; }
	void SetMaxPitch(float pitch) { m_maxPitch = pitch; }
private:
	// Rotation/sec speed of pitch
	float m_pitchSpeed;
	// Maximum pitch deviation from forward
	float m_maxPitch;
	// Current pitch
	float m_pitch;
};

