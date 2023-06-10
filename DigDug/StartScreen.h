#pragma once
#include <string>
#include "BaseComponent.h"
using namespace dae;
namespace digdug
{
	enum StartScreenChoice
	{
		SinglePlayer = 0,
		CoOp = 1
	};
	class StartScreen final : public BaseComponent
	{
	public:
		StartScreen();
		virtual ~StartScreen() = default;
	
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;

		void HandleAction(int amount);
		std::string GetAction() const { return m_Action; };
		void ActivateAction(std::string action);
	private:
		std::string m_Action;
		int m_Number = 0;
		StartScreenChoice m_StartScreen;

	
	};
}


