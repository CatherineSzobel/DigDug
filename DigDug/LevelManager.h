#pragma once
#include "Singleton.h"
#include "Scene.h"
#include <fstream>
#include <string>
#include "RockComponent.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Enemies/PookaComponent.h"
#include "Enemies/FygarsComponent.h"
#include "DigDugCommand.h"
#include "HealthComponent.h"
#include <vector>
#include "ExtraStructs.h"
#include "TileComponent.h"
#include "SceneManager.h"
#include "Enemies/EnemyManager.h"
namespace dae
{
	class LevelManager final : public Singleton<LevelManager>
	{
	public:
		void LoadLevel(std::string filename, Scene& scene);
		void LoadCoopLevel(std::string filename, Scene& scene);
		void CreateInputSolo(std::unique_ptr<GameObject>& firstSprite);
		void CreateInput_Coop(std::unique_ptr<GameObject>& firstSprite, std::unique_ptr<GameObject>& secondSprite);
	private:
	};
}


