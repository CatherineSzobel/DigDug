#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include "Singleton.h"
#include <vector>
#include <map>
#include <memory>
#include "Command.h"
#include "Controller.h"
#include "ControllerButton.h"
namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void Initialize();
		void BindControllerCommand(ControllerButton button, Command* command, InputType inputType);
		void BindKeyboardCommand(SDL_KeyCode key, Command* command, InputType inputType);
	private:
		XINPUT_STATE m_CurrentState[XUSER_MAX_COUNT];
		XINPUT_STATE m_PreviousState{};

		//XINPUT_KEYSTROKE m_CurrentKeyStroke[XUSER_MAX_COUNT];

		using ControllerCommandsMap = std::map<std::pair<ControllerButton, std::unique_ptr<Command>>,InputType>;
		ControllerCommandsMap m_ConsoleButtons{};
		
		using KeyboardCommandsMap = std::map<std::pair<SDL_KeyCode, std::unique_ptr<Command>>, InputType>;
		KeyboardCommandsMap m_KeyboardButtons{};

		std::vector<std::unique_ptr<Controller>> m_pControllers{};
	};

}
