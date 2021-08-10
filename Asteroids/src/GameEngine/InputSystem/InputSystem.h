#pragma once

#include <SDL/SDL.h>
#include <glm/glm.hpp>

enum class ButtonState
{
	NONE,
	PRESSED,
	RELEASED,
	HELD
};

class KeyboardState
{
public:
	friend class InputSystem;

	bool GetKeyValue(SDL_Scancode keyCode) const;
	ButtonState GetKeyState(SDL_Scancode keyCode) const;

private:
	const Uint8 *m_currState; // pointer to the keystate buffer
	Uint8 m_prevState[SDL_NUM_SCANCODES]; // a snapshot of the previous keyboard state

};

class MouseState
{
public:
	friend class InputSystem;

	// Mouse position
	const glm::vec2 &GetPosition() const { return m_mousePos; }

	// Mouse buttons
	bool GetButtonValue(int button) const;
	ButtonState GetButtonState(int button) const;

private:
	glm::vec2 m_mousePos;
	Uint32 m_currButtons;
	Uint32 m_prevButtons;
	bool m_isRelative;
};



struct InputState
{
	KeyboardState keyboard;
	MouseState mouse;
};

class InputSystem
{
public:
	bool Init();
	void Shutdown();
	void EnableRelativeMouse(bool value);
	void BeforeUpdate(); // called before PollEvents
	void Update(); // called after PollEvents
	const InputState &GetState() const { return m_state; }
private:
	InputState m_state;
};
