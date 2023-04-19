#include "Controller.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
//Implementation
dae::Controller::ControllerImpl::ControllerImpl(unsigned int controllerID, ControllerCommandsMap consoleButtons)
{
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	m_ControllerIndex = controllerID;
	m_ConsoleButtons = std::move(consoleButtons);
}

void dae::Controller::ControllerImpl::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	buttonPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	buttonReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

}

bool dae::Controller::ControllerImpl::IsDownThisFrame(unsigned int button) const
{
	return  buttonPressedThisFrame & static_cast<int>(button);
}

bool dae::Controller::ControllerImpl::IsUpThisFrame(unsigned int button) const
{
	return  buttonReleasedThisFrame & static_cast<int>(button);
}

bool dae::Controller::ControllerImpl::IsPressed(unsigned int button) const
{
	return  ((m_CurrentState.Gamepad.wButtons & static_cast<int>(button)) != 0);
}

dae::Controller::Controller(int controllerID, ControllerCommandsMap consoleButtons)
{
    pImpl = new ControllerImpl(controllerID, consoleButtons);
}
dae::Controller::~Controller()
{
    delete pImpl;
}
void dae::Controller::Update()
{
    pImpl->Update();

}

bool dae::Controller::IsDown(ControllerButton button) const
{
	return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool dae::Controller::IsUp(ControllerButton button) const
{
	return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool dae::Controller::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}

dae::ControllerCommandsMap dae::Controller::GetButtons()
{
	return pImpl->GetButtonsImpl();
}
