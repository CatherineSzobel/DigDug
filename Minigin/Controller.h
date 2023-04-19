#pragma once
<<<<<<< HEAD
//#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
=======

>>>>>>> 2c0c54a1826fa96f259d51f05e4c66d7afc2865b
#include <memory>
#include "Command.h"
#include "ControllerButton.h"
#include <map>
#include <SDL.h>
namespace dae
{
	using ControllerCommandsMap = std::map<std::pair<ControllerButton, Command*>, InputType>;

	class Controller final
	{
		class ControllerImpl final
		{
		public:
			ControllerImpl(unsigned int controllerID, ControllerCommandsMap consoleButtons);
			void Update();

			bool IsDownThisFrame(unsigned int button) const;
			bool IsUpThisFrame(unsigned int button) const;
			bool IsPressed(unsigned int button) const;

			ControllerCommandsMap GetButtonsImpl() {return m_ConsoleButtons;}

		private:

			XINPUT_STATE m_CurrentState{};
			XINPUT_STATE m_PreviousState{};
			XINPUT_KEYSTROKE m_CurrentKeyStroke{};

			int m_ControllerIndex{ 0 };
			ControllerCommandsMap m_ConsoleButtons{};
			WORD buttonPressedThisFrame{ 0 };
			WORD buttonReleasedThisFrame{ 0 };
		};

	public:

		Controller(int controllerID,ControllerCommandsMap consoleButtons);
		virtual ~Controller();
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		void Update();


		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;

		ControllerCommandsMap GetButtons();

	private:

		

		//void DeadzoneLeftThumbstick();
		//void DeadzoneRightThumbStick();
		class ControllerImpl;
		ControllerImpl* pImpl;
	};
}
