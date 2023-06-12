#include "DigDugCommand.h"
#include "LevelManager.h"
void digdug::NextSceneCommand::Execute()
{
	LevelManager levelmanager;
	auto currentLevel = dae::SceneManager::GetInstance().GetCurrentSceneIndex() + 2;
	if (currentLevel == 4)
	{
		
	}
	else
	{
		levelmanager.LoadLevel("level" + std::to_string(currentLevel) + ".txt");
	}
};
