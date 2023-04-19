#pragma once
//#define WIN32_LEAN_AND_MEAN
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
#include "InputComponent.h"
namespace dae
{
	using ControllerCommandsMap = std::map<std::pair<ControllerButton, Command*>, InputType>;
	using KeyboardCommandsMap = std::map<std::pair<SDL_Scancode, Command*>, InputType>;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput();
		void Initialize();
		//void BindControllerCommand(ControllerButton button, Command* command, InputType inputType);
		void BindKeyboardCommand(SDL_Scancode key, Command* command, InputType inputType);

		void AddController(GameObject* gameObject, int controllerID);
		void AddKeyboardController(GameObject* gameObject);

	private:
		XINPUT_STATE m_CurrentState[XUSER_MAX_COUNT];
		XINPUT_STATE m_PreviousState{};

		//XINPUT_KEYSTROKE m_CurrentKeyStroke[XUSER_MAX_COUNT];

		ControllerCommandsMap m_ConsoleButtons{};

		KeyboardCommandsMap m_KeyboardButtons{};
		KeyboardCommandsMap m_GlobalKeyboardButtons{};

		std::vector<std::unique_ptr<Controller>> m_pControllers{};
	};

}
