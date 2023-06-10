#include "Enemy.h"
#include "Game.h"
#include "CollisionManager.h"
digdug::Enemy::Enemy()
{
	auto& currentScene = SceneManager::GetInstance().GetCurrentScene();
	SetScene(&currentScene);
	m_pSubject = new Subject();
	auto TileRowSize = glm::vec2{ 610.f,96.f };
	auto CollisionLeftBottom = glm::vec2{ 0.f,100.f };
	m_LayerPositions.emplace_back(Rectf{ CollisionLeftBottom.x,CollisionLeftBottom.y,TileRowSize.x,TileRowSize.y });
	m_LayerPositions.emplace_back(Rectf{ CollisionLeftBottom.x,CollisionLeftBottom.y + TileRowSize.y,TileRowSize.x,TileRowSize.y });
	m_LayerPositions.emplace_back(Rectf{ CollisionLeftBottom.x,CollisionLeftBottom.y + (TileRowSize.y * 2),TileRowSize.x,TileRowSize.y});
	m_LayerPositions.emplace_back(Rectf{ CollisionLeftBottom.x,CollisionLeftBottom.y + (TileRowSize.y * 3),TileRowSize.x,TileRowSize.y - 32.f });

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

void digdug::Enemy::GetEnemyCurrentLayer()
{
	for (int i = 0; i < m_LayerPositions.size(); i++)
	{
		if (m_pCollisionComp->Collide(m_LayerPositions[i]))
		{
			m_CurrentLayer = i + 1;
		}
	}
}
