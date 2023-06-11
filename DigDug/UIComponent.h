#pragma once
#include <string>
#include "BaseComponent.h"
#include "GameState.h"
using namespace dae;
namespace digdug
{
	enum StartScreenChoice
	{
		SinglePlayer = 0,
		CoOp = 1
	};
	class UIComponent final : public BaseComponent
	{
	public:
		UIComponent();
		virtual ~UIComponent();
	
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;

		void HandleAction(int amount);
		std::string GetAction() const { return m_Action; };
		void ActivateAction(std::string action);
		bool GetIsActionPicked() const { return m_ActionPicked; };
		int GetNumber() const { return m_Number; };
	private:
		std::string m_Action;
		int m_Number = 0;
		StartScreenChoice m_StartScreen;
		bool m_ActionPicked;
		GameState* m_pCurrentState = nullptr;
	
	};
}


