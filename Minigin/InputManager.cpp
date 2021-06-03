#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	for (auto& temp : m_Controls)
	{
		if (IsPressed(temp.first))
		{
			temp.second->Execute();

		}
	}

	return true;
}

bool InputManager::IsPressed(ControllerButton button)
{
	// todo: return whether the given button is pressed or not.
	bool ButtonPress = false;
	for (auto& temp : m_LastFrameInput)
	{
		if (temp.first == button)
		{
			if (temp.second == false)
			{
				ButtonPress = ((m_CurrentState.Gamepad.wButtons & int(button)) != 0);
				if (ButtonPress)
				{
					temp.second = true;
				}
			}
		}
	}

	// This currently just resets the buttondown, later this should be called from another place to check for OnButtonRelease commands
	OnButtonRelease(button);
	return ButtonPress;
}

bool InputManager::OnButtonRelease(ControllerButton button)
{
	bool ButtonPress = false;
	for (auto& temp : m_LastFrameInput)
	{
		if (temp.first == button)
		{
			if (temp.second == true)
			{
				ButtonPress = ((m_CurrentState.Gamepad.wButtons & int(button)) != 0);
				if (!ButtonPress)
				{
					temp.second = false;
				}
			}
		}
	}

	return ButtonPress;
}

void InputManager::BindCommand(ControllerButton button, Command* com)
{
	m_LastFrameInput.insert(std::pair<ControllerButton, bool>(button, false));
	m_Controls.insert(std::pair<ControllerButton, Command*>(button, com));
}

void InputManager::RunCommand(ControllerButton button)
{
	auto temp = m_Controls.at(button);
	temp->Execute();
}


