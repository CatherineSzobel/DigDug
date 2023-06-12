#pragma once
#include "Scene.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "SceneManager.h"
#include "Subject.h"
namespace digdug
{

	class Enemy
	{
	public:
		Enemy();
		virtual ~Enemy();
		bool IsActive() const { return m_IsActive; };
		void SetActive(bool flag);
		dae::Scene* GetScene() const { return m_Scene; };
		dae::Subject* GetSubject() { return m_pSubject; };
		void IncreasePump();
		virtual void Release() = 0;
		void Reset();
	protected:
		void HandleOnDeath(dae::GameObject* obj);
		void HandleOnHit(std::string animation);
		void DeathByRock();
		void SetScene(dae::Scene* scene);
		dae::SpriteComponent* m_pSpriteComp = nullptr;
		dae::CollisionComponent* m_pCollisionComp = nullptr;
		bool m_Attached = false;
		bool m_IsHit = false;
		bool m_IsDead = false;
		bool m_DeathByRock = false;
		int m_AmountOfPumps;

		dae::Subject* m_pSubject = nullptr;
		std::vector<Rectf> m_LayerPositions;
		void GetEnemyCurrentLayer();
		int m_CurrentLayer = 0;
	private:
		bool m_IsActive = true;
		dae::Scene* m_Scene = nullptr;
	};
}

