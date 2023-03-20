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

	return true;
}

void dae::InputManager::Initialize()
{
}

void dae::InputManager::BindControllerCommand(ControllerButton button, Command* command)
{
	m_ConsoleButtons.emplace(button, std::unique_ptr<Command>(command));
}

void dae::InputManager::BindKeyboardCommand(SDL_KeyCode key, Command* command)
{
	m_KeyboardButtons.emplace(key, std::unique_ptr<Command>(command));
}
