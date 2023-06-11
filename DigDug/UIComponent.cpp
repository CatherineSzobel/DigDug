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
	//if (m_Number < 0)
	//{
	//	m_Number = (int)CoOp;
	//}
	//else if (m_Number > (int)CoOp)
	//{
	//	m_Number = 0;
	//}

	//switch (m_Number)
	//{
	//case digdug::SinglePlayer:
	//	m_Action = "SinglePlayer";
	//	break;
	//case digdug::CoOp:
	//	m_Action = "CoOp";
	//	break;
	//}
}

void digdug::UIComponent::ActivateAction(std::string action)
{
	m_ActionPicked = true;
	//if (action == "SinglePlayer")
	//{
	//	printf("start singleplayer mode");
	//	auto& firstLevel = dae::SceneManager::GetInstance().GetCurrentScene();
	//	//auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + "Levels/level1.txt";
	//	firstLevel.RemoveAll();
	//	InputManager::GetInstance().Reset();
	//	LevelManager levelManager;
	//	levelManager.LoadLevel("level1.txt");
	//}
	//if (action == "CoOp")
	//{
	//	printf("start co op mode");
	//	auto& firstLevel = dae::SceneManager::GetInstance().GetCurrentScene();
	//	firstLevel.RemoveAll();
	//	InputManager::GetInstance().Reset();
	//	LevelManager levelManager;
	//	levelManager.LoadCoopLevel("level1.txt");
	//}
}
