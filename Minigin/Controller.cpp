#include "Controller.h"
//using ControllerCommandsMap = std::map<std::pair<ControllerButton, std::unique_ptr<Command>>, InputType>;
class dae::Controller::ControllerImpl final
{
public:
	using ControllerCommandsMap = std::map<std::pair<dae::ControllerButton, dae::Command*>, dae::InputType>;

	//Implementation
	ControllerImpl(unsigned int controllerID, ControllerCommandsMap consoleButtons)
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		m_ControllerIndex = controllerID;
		m_ConsoleButtons = std::move(consoleButtons);
	}

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		buttonPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		buttonReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

	}

	bool IsDownThisFrame(unsigned int button) const
	{
		return  buttonPressedThisFrame & static_cast<int>(button);
	}

	bool IsUpThisFrame(unsigned int button) const
	{
		return  buttonReleasedThisFrame & static_cast<int>(button);
	}

	bool IsPressed(unsigned int button) const
	{
		return  ((m_CurrentState.Gamepad.wButtons & static_cast<int>(button)) != 0);
	}

	ControllerCommandsMap GetButtonsImpl() { return m_ConsoleButtons; }

private:

	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};
	XINPUT_KEYSTROKE m_CurrentKeyStroke{};

	int m_ControllerIndex{ 0 };
	ControllerCommandsMap m_ConsoleButtons{};
	WORD buttonPressedThisFrame{ 0 };
	WORD buttonReleasedThisFrame{ 0 };
};


dae::Controller::Controller(int controllerID, ControllerCommandsMap consoleButtons)
{
    pImpl = new dae::Controller::ControllerImpl(controllerID, consoleButtons);
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
