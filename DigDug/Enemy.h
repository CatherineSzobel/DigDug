#pragma once
#include "Scene.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "SceneManager.h"
#include "Subject.h"

using namespace dae;
namespace digdug
{

	class Enemy
	{
	public:
		Enemy();
		virtual ~Enemy();
		bool IsActive() const { return m_IsActive; };
		void SetActive(bool flag);
		Scene* GetScene() const { return m_Scene; };
		Subject* GetSubject() { return m_pSubject; };
		void IncreasePump();
		void Reset();
	protected:
		void HandleOnDeath(GameObject* obj);
		void HandleOnHit(std::string animation);

		void SetScene(Scene* scene);
		SpriteComponent* m_pSpriteComp = nullptr;
		CollisionComponent* m_pCollisionComp = nullptr;
		bool m_Attached = false;
		bool m_IsHit = false;
		bool m_IsDead = false;
		int m_AmountOfPumps;

	//	TileType m_CurrentTileType;
	private:
		bool m_IsActive = true;
		Scene* m_Scene = nullptr;
		Subject* m_pSubject = nullptr;
	};
}

