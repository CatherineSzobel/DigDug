#include <SDL.h>
#include "InputManager.h"
#include <iostream>
#include "..\3rdParty\imgui\imgui_impl_sdl2.h"
bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			for (auto& command : m_KeyboardButtons)
			{
				if (command.second == InputType::Down && e.key.keysym.sym == command.first.first)
				{
					command.first.second.get()->Execute();
				}
			}
			for (auto& command : m_KeyboardButtons)
			{
				if (command.second == InputType::Up && e.key.keysym.sym == command.first.first)
				{
					command.first.second.get()->Execute();
				}
			}
		}
		if (e.type == SDL_KEYUP)
		{
	
			for (auto& keyboardButton : m_KeyboardButtons)
			{
				if (keyboardButton.second == InputType::Press && e.key.keysym.sym == keyboardButton.first.first)
				{
					keyboardButton.first.second.get()->Execute();
				}
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	for (auto& controller : m_pControllers)
	{
		controller->Update();
		for (auto& button : m_ConsoleButtons)
		{
			if ( button.second == InputType::Up && controller->IsUp(button.first.first))
			{
				button.first.second.get()->Execute();
			}
			if (button.second == InputType::Press && controller->IsPressed(button.first.first))
			{
				button.first.second.get()->Execute();
			}
			if (button.second == InputType::Down && controller->IsDown(button.first.first))
			{
				button.first.second.get()->Execute();
			}
		}
	}
	return true;
}

void dae::InputManager::Initialize()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{

		ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));

		auto dwResult = XInputGetState(i, &m_CurrentState[i]);

		//determine if the controller is connected
		if (dwResult == ERROR_SUCCESS)
		{
			//Controller is connected
			m_pControllers.emplace_back(new Controller(i));
		}
		else
		{
			ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));
			break;
			//Controller is not connected
		}
	}
}

void dae::InputManager::BindControllerCommand(ControllerButton button, Command* command, InputType inputType)
{
	m_ConsoleButtons.emplace(std::make_pair(button, std::unique_ptr<Command>(command)),inputType);
}

void dae::InputManager::BindKeyboardCommand(SDL_KeyCode key, Command* command, InputType inputType)
{
	m_KeyboardButtons.emplace(std::make_pair(key, std::unique_ptr<Command>(command)), inputType);
}
