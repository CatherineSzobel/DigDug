#pragma once
#include "Singleton.h"
#include "Enemy.h"
#include "Scene.h"
#include "Subject.h"
namespace digdug
{
	class EnemyManager final : public dae::Singleton<EnemyManager>
	{
	public:
		int EnemiesLeft() const;
		void AddEnemies(Enemy* enemy);
		void SetEnemiesActive();
		std::vector<Enemy*> GetEnemies() {return std::move(m_Enemies);};
		Enemy* GetEnemyPointer(const int i);

	private:
		std::vector< Enemy*> m_Enemies;

	};
}


