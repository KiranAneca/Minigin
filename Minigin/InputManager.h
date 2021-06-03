#pragma once
#include <Windows.h>
#include <XInput.h>
#include <map>
#include "Singleton.h"
#include "Command.h"

	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button);
		bool OnButtonRelease(ControllerButton button);

		void BindCommand(ControllerButton button, Command* com);
		void RunCommand(ControllerButton button);
	private:
		friend class Singleton<InputManager>;
		InputManager() = default;
		
		XINPUT_STATE m_CurrentState{};
		std::map<ControllerButton, Command*> m_Controls;
		std::map<ControllerButton, bool> m_LastFrameInput;
	};
