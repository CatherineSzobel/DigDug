#pragma once
//#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
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
	public:

		explicit Controller(int controllerID,ControllerCommandsMap consoleButtons);
		virtual ~Controller();
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		void Update();


		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;

		ControllerCommandsMap GetButtons() const;

	private:
		class ControllerImpl;
		ControllerImpl* pImpl;
	};
}
