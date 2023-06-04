#include "Enemy.h"

digdug::Enemy::Enemy()
{
	auto& currentScene = SceneManager::GetInstance().GetCurrentScene();
	SetScene(&currentScene);
}

void digdug::Enemy::SetActive(bool flag)
{
	m_IsActive = flag;
}

void digdug::Enemy::IncreasePump()
{
	if (m_AmountOfPumps == 3)
	{
		//enemy dies
		m_IsDead = true;
	}
	else
	{
		++m_AmountOfPumps;
	}
}

void digdug::Enemy::Reset()
{
	m_AmountOfPumps = 0;
}

void digdug::Enemy::SetScene(Scene* scene)
{
	m_Scene = scene;
}
