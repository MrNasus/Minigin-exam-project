#pragma once
#include "Singleton.h"
#include <vector>
#include <unordered_map>
#include <Windows.h>
#include <XInput.h>

namespace minigin
{
	enum class ControllerButton
	{
		DpadLeft,
		DpadRight,
		DpadUp,
		DpadDown,
		ButtonA,
		ButtonB,
		ButtonStart,
		None
	};

	enum class KeyboardButton
	{
		Left,
		Right,
		Up,
		Down,
		Escape,
		Space,
		None
	};

	enum class InputTriggerState
	{
		Pressed,
		Released,
		Down
	};

	struct InputBinding
	{
		InputBinding() 
			:Id (-1)
			,TriggerState (InputTriggerState::Pressed)
			,Controller (ControllerButton::None)
			,Keyboard (KeyboardButton::None)
			,IsTriggered (false)
		{}

		InputBinding(int id, InputTriggerState triggerState = InputTriggerState::Pressed, ControllerButton controller = ControllerButton::None, KeyboardButton keyboard = KeyboardButton::None) 
			:Id (id)
			,TriggerState (triggerState)
			,Controller (controller)
			,Keyboard (keyboard)
			,IsTriggered (false)
		{}

		int Id;
		InputTriggerState TriggerState;
		ControllerButton Controller;
		KeyboardButton Keyboard;
		bool IsTriggered;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Init();
		void SetQuit(bool quit);
		bool GetQuit() const;
		void ProcessInput();
		void AddInputBinding(const InputBinding& inputBinding);
		bool IsBindingTriggered(int id) const;

	private:
		XINPUT_STATE m_CurrentState{};
		std::vector<bool> m_KeyboardButtons;
		std::vector<bool> m_PreviousKeyboardButtons;
		std::vector<bool> m_ControllerButtons;
		std::vector<bool> m_PreviousControllerButtons;
		std::unordered_map<int, InputBinding> m_InputBindings;
		bool m_Quit;
	};

}
