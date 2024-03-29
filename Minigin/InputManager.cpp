#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


InputManager::~InputManager()
{
	for(auto com : m_KeyboardControls)
	{
		delete com.second;
	}
	for(auto com : m_Controls)
	{
		delete com.second;
	}
}

bool InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		for (auto& temp : m_KeyboardControls)
		{
			if(e.type == SDL_KEYUP)
			{
				if(temp.first == e.key.keysym.scancode)
				{
					temp.second->Execute();
				}
			}
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
	if(m_Controls.find(button) == m_Controls.end())
	{
		m_LastFrameInput.insert(std::pair<ControllerButton, bool>(button, false));
		m_Controls.insert(std::pair<ControllerButton, Command*>(button, com));
	}
	else
	{
		delete m_Controls.at(button);
		m_Controls.at(button) = com;
	}
}

void InputManager::BindCommand(SDL_Scancode button, Command* com)
{
	if(m_KeyboardControls.find(button) == m_KeyboardControls.end())
	{
		m_KeyboardControls.insert(std::pair<SDL_Scancode, Command*>(button, com));
	}
	else
	{
		delete m_KeyboardControls.at(button);
		m_KeyboardControls.at(button) = com;
	}
}

void InputManager::RunCommand(ControllerButton button)
{
	auto temp = m_Controls.at(button);
	temp->Execute();
}


