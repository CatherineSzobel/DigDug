#pragma once
#include "Scene.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "SceneManager.h"
using namespace dae;
namespace digdug
{

	class Enemy
	{
	public:
		Enemy();
		virtual ~Enemy() {};
		bool IsActive() const { return m_IsActive; };
		void SetActive(bool flag);
		Scene* GetScene() const { return m_Scene; };
		void IncreasePump();
		void Reset();
		int GetAmountOfPumps() { return m_AmountOfPumps; };
	protected:
		void SetScene(Scene* scene);
		SpriteComponent* m_pSpriteComp = nullptr;
		CollisionComponent* m_pCollisionComp = nullptr;
		bool m_Attached = false;
		bool m_IsDead = false;
		int m_AmountOfPumps;
	private:
		bool m_IsActive = true;
		Scene* m_Scene = nullptr;
	};
}

