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
		Reset();
	}
	else
	{
		m_IsHit = true;
		++m_AmountOfPumps;
	}
}

void digdug::Enemy::Reset()
{
	m_AmountOfPumps = 0;
}

void digdug::Enemy::HandleOnDeath(GameObject* obj)
{
	obj->MarkForDeletion(true);
	m_pCollisionComp->SetCollision(false);
	SetActive(false);
}

void digdug::Enemy::HandleOnHit(std::string animation)
{
	m_pSpriteComp->SetAnimationByName(animation);
	m_pSpriteComp->IncreaseSpriteFrame();
	m_IsHit = false;
}

void digdug::Enemy::SetScene(Scene* scene)
{
	m_Scene = scene;
}
