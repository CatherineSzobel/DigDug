#pragma once
#include "SDL.h"
#include "ControllerButton.h"
#include "BaseComponent.h"
#include <map>
#include <memory>
#include "GameObject.h"

namespace dae
{
	class Command;
	using ControllerCommandsMap = std::map<std::pair<ControllerButton, Command*>, InputType>;
	using KeyboardCommandsMap = std::map<std::pair<SDL_KeyCode, Command*>, InputType>;
	class InputComponent final : public BaseComponent
	{
	public:
		// Inherited via BaseComponent
		explicit InputComponent() {};

		virtual ~InputComponent();
		InputComponent(const InputComponent& other) = delete;
		InputComponent(InputComponent&& other) = delete;
		InputComponent& operator=(const InputComponent& other) = delete;
		InputComponent& operator=(InputComponent&& other) = delete;

		//virtual void Initialize() override;
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;

		void MoveUp();
		void MoveLeft();
		void MoveRight();
		void MoveDown();

		void BindControllerCommand(ControllerButton button, Command* command, InputType inputType);
		void BindKeyboardCommand(SDL_KeyCode key, Command* command, InputType inputType);
		void SetMovementSpeed(float movementSpeed);
		ControllerCommandsMap GetButtons();
		KeyboardCommandsMap GetKeyboardButtons();
	private:

		ControllerCommandsMap m_ConsoleButtons{};
		KeyboardCommandsMap m_KeyboardButtons{};

		float m_MovementSpeed{ 5.f };

	};
}