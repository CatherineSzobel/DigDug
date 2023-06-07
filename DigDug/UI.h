#pragma once
#include <string>
#include "BaseComponent.h"
using namespace dae;
namespace digdug
{
	enum StartScreen
	{
		SinglePlayer = 0,
		CoOp = 1
	};
	class UI final : public BaseComponent
	{
	public:
		UI();
		virtual ~UI() = default;
	
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
		StartScreen m_StartScreen;

	
	};
}


