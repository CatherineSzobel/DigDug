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
		if (e.type == SDL_KEYDOWN) {
			std::cout << "e";
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	for (auto& controller : m_pControllers)
	{
		controller->Update();
		for (auto& command : m_ConsoleButtons)
		{
			if ( command.second == InputType::Up && controller->IsUp(command.first.first))
			{
				command.first.second.get()->Execute();
				break;
			}
			if (command.second == InputType::Press && controller->IsPressed(command.first.first))
			{
				command.first.second.get()->Execute();
				break;
			}
			if (command.second == InputType::Down && controller->IsDown(command.first.first))
			{
				command.first.second.get()->Execute();
				break;
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
