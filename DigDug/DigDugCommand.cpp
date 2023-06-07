#include "DigDugCommand.h"
#include "LevelManager.h"
void digdug::NextSceneCommand::Execute()
{
	LevelManager levelManager;
	levelManager.LoadLevel("level2.txt");
};
