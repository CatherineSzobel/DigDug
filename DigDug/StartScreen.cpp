#include "StartScreen.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include "InputManager.h"
digdug::StartScreen::StartScreen()
	:m_Action{ "SinglePlayer" }, m_Number{ 0 }, m_StartScreen{ SinglePlayer }
{
}

void digdug::StartScreen::Render()
{
}

void digdug::StartScreen::Update(float)
{
}

void digdug::StartScreen::FixedUpdate(float)
{
}


void digdug::StartScreen::HandleAction(int amount)
{
	m_Number += amount;
	if (m_Number < 0)
	{
		m_Number = (int)CoOp;
	}
	else if (m_Number > (int)CoOp)
	{
		m_Number = 0;
	}

	switch (m_Number)
	{
	case digdug::SinglePlayer:
		m_Action = "SinglePlayer";
		break;
	case digdug::CoOp:
		m_Action = "CoOp";
		break;
	}
}

void digdug::StartScreen::ActivateAction(std::string action)
{
	if (action == "SinglePlayer")
	{
		printf("start singleplayer mode");
		auto& firstLevel = dae::SceneManager::GetInstance().GetCurrentScene();
		//auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + "Levels/level1.txt";
		firstLevel.RemoveAll();
		InputManager::GetInstance().Reset();
		LevelManager levelManager;
		levelManager.LoadLevel("level1.txt");
	}
	if (action == "CoOp")
	{
		printf("start co op mode");
		auto& firstLevel = dae::SceneManager::GetInstance().GetCurrentScene();
		firstLevel.RemoveAll();
		InputManager::GetInstance().Reset();
		LevelManager levelManager;
		levelManager.LoadCoopLevel("level1.txt");
	}
}
