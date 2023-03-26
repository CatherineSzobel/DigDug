#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include <vector>
#include <memory>
#include "Command.h"
#include "ControllerButton.h"
#include <map>
#include <SDL.h>
namespace dae
{

	class Controller final
	{
		class ControllerImpl final
		{
		public:
			ControllerImpl(unsigned int controllerID);
			void Update();

			bool IsDownThisFrame(unsigned int button) const;
			bool IsUpThisFrame(unsigned int button) const;
			bool IsPressed(unsigned int button) const;


		private:

			XINPUT_STATE m_CurrentState{};
			XINPUT_STATE m_PreviousState{};
			XINPUT_KEYSTROKE m_CurrentKeyStroke{};

			int m_ControllerIndex{ 0 };
			WORD buttonPressedThisFrame{ 0 };
			WORD buttonReleasedThisFrame{ 0 };
		};

	public:

		Controller(int controllerID);
		virtual ~Controller();
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		void Update();


		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;

	private:
		//void DeadzoneLeftThumbstick();
		//void DeadzoneRightThumbStick();
		class ControllerImpl;
		ControllerImpl* pImpl;
	};
}
