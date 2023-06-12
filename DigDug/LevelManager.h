#pragma once
#include "Singleton.h"
#include "Scene.h"
#include <fstream>
#include <string>
#include "RockComponent.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "PookaComponent.h"
#include "FygarsComponent.h"
#include "HealthComponent.h"
#include <vector>
#include "ExtraStructs.h"
#include "TileComponent.h"
#include "SceneManager.h"
#include "EnemyManager.h"
#include "DigDugCommand.h"
namespace digdug
{
	enum ControllerType
	{
		keyboard,
		controller,
		both
	};
	class LevelManager final
	{
	public:
		void LoadLevel(std::string filename);
		void LoadCoopLevel(std::string filename);
		int ReadHighScoreFromFile();
		void SaveHighScoreInFile(int highScore);
	private:
		void CreateInputSolo(std::unique_ptr<dae::GameObject>& sprite, ControllerType type);
		void IncreaseRow(int& x,int& y,int maxtilecolumn);
		bool m_LevelCleared = false;
	};
}


