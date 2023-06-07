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
#include "DigDugCommand.h"
#include "HealthComponent.h"
#include <vector>
#include "ExtraStructs.h"
#include "TileComponent.h"
#include "SceneManager.h"
#include "EnemyManager.h"
using namespace dae;
namespace digdug
{
	class LevelManager final : public Singleton<LevelManager>
	{
	public:
		void LoadLevel(std::string filename);
		void LoadCoopLevel(std::string filename);
		void CreateInputSolo(std::unique_ptr<GameObject>& firstSprite);
		void CreateInput_Coop(std::unique_ptr<GameObject>& firstSprite, std::unique_ptr<GameObject>& secondSprite);
	private:
		void IncreaseRow(int& x,int& y,int maxtilecolumn);
	};
}


