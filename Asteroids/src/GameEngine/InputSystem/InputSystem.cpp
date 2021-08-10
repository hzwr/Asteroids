#include "InputSystem.h"
#include <algorithm>

bool InputSystem::Init()
{

	m_state.keyboard.m_currState = SDL_GetKeyboardState(NULL); // get the keyboard state pointer
	std::fill_n(m_state.keyboard.m_prevState, SDL_NUM_SCANCODES, 0); // clear the states
	return true;
}

void InputSystem::Shutdown()
{
}

void InputSystem::EnableRelativeMouse(bool value)
{
	SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);
	m_state.mouse.m_isRelative = value;
}

void InputSystem::BeforeUpdate()
{
	// Get a snapshot of the keyboard state
	std::copy(m_state.keyboard.m_currState,
		m_state.keyboard.m_currState + SDL_NUM_SCANCODES,
		m_state.keyboard.m_prevState
	);

	// Get a snapshot of the mouse state
	m_state.mouse.m_prevButtons = m_state.mouse.m_currButtons;

}

void InputSystem::Update()
{
	// Mouse
	int x = 0, y = 0;
	if (m_state.mouse.m_isRelative)
	{
		m_state.mouse.m_currButtons =
			SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		m_state.mouse.m_currButtons =
			SDL_GetMouseState(&x, &y);
	}

	m_state.mouse.m_mousePos.x = static_cast<float>(x);
	m_state.mouse.m_mousePos.y = static_cast<float>(y);

}

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	return m_currState[keyCode] == 1;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (m_prevState[keyCode] == 0)
	{
		if (m_currState[keyCode] == 0)
		{
			return ButtonState::NONE;
		}
		else
		{
			return ButtonState::PRESSED;
		}
	}
	else
	{
		if (m_currState[keyCode] == 0)
		{
			return ButtonState::RELEASED;
		}
		else
		{
			return ButtonState::HELD;
		}
	}
}

bool MouseState::GetButtonValue(int button) const
{
	return (SDL_BUTTON(button) & m_currButtons) == 1;
}

ButtonState MouseState::GetButtonState(int button) const
{
	int mask = SDL_BUTTON(button);
	if ((mask & m_prevButtons) == 0)
	{
		if ((mask & m_currButtons) == 0)
		{
			return ButtonState::NONE;
		}
		else
		{
			return ButtonState::PRESSED;
		}
	}
	else
	{
		if ((mask & m_currButtons) == 0)
		{
			return ButtonState::RELEASED;
		}
		else
		{
			return ButtonState::HELD;
		}

	}
}
