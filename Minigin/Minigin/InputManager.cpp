#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

using namespace minigin;

void InputManager::Init()
{
	m_Quit = false;
	m_ControllerButtons.assign(size_t(ControllerButton::None) + 1, false);
	m_PreviousControllerButtons.assign(m_ControllerButtons.size(), false);
	m_KeyboardButtons.assign(size_t(KeyboardButton::None) + 1, false);
	m_PreviousKeyboardButtons.assign(m_KeyboardButtons.size(), false);
}

void InputManager::SetQuit(bool quit)
{
	m_Quit = quit;
}

bool InputManager::GetQuit() const
{
	return m_Quit;
}

void InputManager::ProcessInput()
{
	//process controller buttons
	size_t controllerSize = m_ControllerButtons.size();
	for (size_t i = 0; i < controllerSize; ++i)
	{
		m_PreviousControllerButtons[i] = m_ControllerButtons[i];
	}

	m_ControllerButtons.assign(m_ControllerButtons.size(), false);

	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		m_ControllerButtons[size_t(ControllerButton::DpadLeft)] = true;
	}
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		m_ControllerButtons[size_t(ControllerButton::DpadRight)] = true;
	}
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		m_ControllerButtons[size_t(ControllerButton::DpadUp)] = true;
	}
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		m_ControllerButtons[size_t(ControllerButton::DpadDown)] = true;
	}
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		m_ControllerButtons[size_t(ControllerButton::ButtonA)] = true;
	}
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
	{
		m_ControllerButtons[size_t(ControllerButton::ButtonB)] = true;
	}
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_START)
	{
		m_ControllerButtons[size_t(ControllerButton::ButtonStart)] = true;
	}

	//process keyboard buttons
	size_t keyboardSize = m_KeyboardButtons.size();
	for (size_t i = 0; i < keyboardSize; ++i)
	{
		m_PreviousKeyboardButtons[i] = m_KeyboardButtons[i];
	}

	m_KeyboardButtons.assign(m_KeyboardButtons.size(), false);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) 
		{
			m_Quit = true;
		}
		if (e.key.keysym.sym == SDL_SCANCODE_LEFT) 
		{
			m_KeyboardButtons[size_t(KeyboardButton::Left)] = true;
		}
		if (e.key.keysym.sym == SDL_SCANCODE_RIGHT) 
		{
			m_KeyboardButtons[size_t(KeyboardButton::Right)] = true;
		}
		if (e.key.keysym.sym == SDL_SCANCODE_UP) 
		{
			m_KeyboardButtons[size_t(KeyboardButton::Up)] = true;
		}
		if (e.key.keysym.sym == SDL_SCANCODE_DOWN) 
		{
			m_KeyboardButtons[size_t(KeyboardButton::Down)] = true;
		}
		if (e.key.keysym.sym == SDL_SCANCODE_ESCAPE) 
		{
			m_KeyboardButtons[size_t(KeyboardButton::Escape)] = true;
		}
		if (e.key.keysym.sym == SDL_SCANCODE_SPACE) 
		{
			m_KeyboardButtons[size_t(KeyboardButton::Space)] = true;
		}
	}

	//update input bindings
	for (auto it = m_InputBindings.begin(); it != m_InputBindings.end() ; ++it)
	{
		auto currentBinding = &(it->second);

		currentBinding->IsTriggered = false;

		switch (currentBinding->TriggerState)
		{
		case InputTriggerState::Down:
			if (m_ControllerButtons[size_t(currentBinding->Controller)] || m_KeyboardButtons[size_t(currentBinding->Keyboard)])
			{
				currentBinding->IsTriggered = true;
			}
			break;
		case InputTriggerState::Pressed:
			if ((!m_PreviousControllerButtons[size_t(currentBinding->Controller)] && m_ControllerButtons[size_t(currentBinding->Controller)])
				|| (!m_PreviousKeyboardButtons[size_t(currentBinding->Keyboard)] && m_KeyboardButtons[size_t(currentBinding->Keyboard)]))
			{
				currentBinding->IsTriggered = true;
			}
			break;
		case InputTriggerState::Released:
			if ((m_PreviousControllerButtons[size_t(currentBinding->Controller)] && !m_ControllerButtons[size_t(currentBinding->Controller)])
				|| (m_PreviousKeyboardButtons[size_t(currentBinding->Keyboard)] && !m_KeyboardButtons[size_t(currentBinding->Keyboard)]))
			{
				currentBinding->IsTriggered = true;
			}
			break;
		default:
			break;
		}
	}
}

void InputManager::AddInputBinding(const InputBinding& inputBinding)
{
	m_InputBindings[inputBinding.Id] = inputBinding;
}

bool InputManager::IsBindingTriggered(int id) const
{
	return m_InputBindings.find(id)->second.IsTriggered;
}
