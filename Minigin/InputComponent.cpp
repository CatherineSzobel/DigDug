#include "InputComponent.h"
#include "Command.h"
dae::InputComponent::~InputComponent()
{
	for (const auto& button : m_ConsoleButtons)
	{
		delete button.first.second;
	}

	for (const auto& button : m_KeyboardButtons)
	{
		delete button.first.second;
	}
}

void dae::InputComponent::Render()
{
}

void dae::InputComponent::Update(float)
{
}

void dae::InputComponent::FixedUpdate(float)
{
}

void dae::InputComponent::BindControllerCommand(ControllerButton button, Command* command, InputType inputType)
{
	m_ConsoleButtons.emplace(std::make_pair(button, command), inputType);
}

void dae::InputComponent::BindKeyboardCommand(SDL_Scancode key, Command* command, InputType inputType)
{
	m_KeyboardButtons.emplace(std::make_pair(key, command), inputType);
}

void dae::InputComponent::SetMovementSpeed(float movementSpeed)
{
	m_MovementSpeed = movementSpeed;
}

dae::ControllerCommandsMap dae::InputComponent::GetButtons() const
{
	return m_ConsoleButtons;
}

dae::KeyboardCommandsMap dae::InputComponent::GetKeyboardButtons() const
{
	return m_KeyboardButtons;
}
