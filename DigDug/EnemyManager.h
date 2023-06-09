#pragma once
#include "Singleton.h"
#include "Enemy.h"
#include "Scene.h"
#include "Subject.h"
using namespace dae;
namespace digdug
{
	class EnemyManager : public Singleton<EnemyManager>
	{
	public:
		int EnemiesLeft() const;
		void AddEnemies(Enemy* enemy);
		void SetEnemiesActive();
		std::vector<Enemy*> GetEnemies() const {return std::move(m_Enemies);};
		Enemy* GetEnemyPointer(const int i);

	private:
		std::vector< Enemy*> m_Enemies;

	};
}


