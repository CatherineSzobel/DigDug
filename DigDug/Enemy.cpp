#include "Enemy.h"

digdug::Enemy::Enemy()
{
	auto& currentScene = SceneManager::GetInstance().GetCurrentScene();
	SetScene(&currentScene);
	m_pSubject = new Subject();
}
digdug::Enemy::~Enemy()
{
	delete m_pSubject;
	m_pSubject = nullptr;
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
		m_pSubject->Notify(Event::OnPookaFirstLayerDeath);
		m_AmountOfPumps = 0;
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
	m_IsDead = false;
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
