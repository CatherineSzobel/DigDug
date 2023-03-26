#pragma once
#include "SDL.h"
#include "ControllerButton.h"
#include "BaseComponent.h"
#include <map>
#include <memory>
#include "GameObject.h"
//#include "Command.h"

namespace dae
{
	class InputComponent final : public BaseComponent
	{
	public:
		// Inherited via BaseComponent
		explicit InputComponent() {};

		virtual ~InputComponent() = default;
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


	private:
		//using ControllerCommandsMap = std::map<std::pair<ControllerButton, std::unique_ptr<Command>>, InputType>;
		float m_MovementSpeed{ 5.f };
		
	};
}