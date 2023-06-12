#include "UIComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include "InputManager.h"
digdug::UIComponent::UIComponent()
	:m_Action{ "SinglePlayer" }, m_Number{ 0 }, m_StartScreen{ SinglePlayer }
{

}

digdug::UIComponent::~UIComponent()
{
	delete m_pCurrentState;
	m_pCurrentState = nullptr;
}

void digdug::UIComponent::Render()
{

}

void digdug::UIComponent::Update(float elapsed)
{
	auto newState = m_pCurrentState->Update(GetOwner(), elapsed);
	if (newState != nullptr)
	{
		delete m_pCurrentState;
		m_pCurrentState = newState;
	}
}

void digdug::UIComponent::FixedUpdate(float)
{
}

void digdug::UIComponent::Initialize()
{
	m_pCurrentState = new digdug::StartScreenState(GetOwner());
}


void digdug::UIComponent::HandleAction(int amount)
{
	m_Number += amount;

}

void digdug::UIComponent::ActivateAction(std::string action)
{
	m_ActionPicked = true;
}
