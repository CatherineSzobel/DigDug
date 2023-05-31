#pragma once
#include "Scene.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "SceneManager.h"
namespace dae
{

	class Enemy
	{
	public:
		Enemy();
		virtual ~Enemy() {};
		bool IsActive() const { return m_IsActive; };
		void SetActive(bool flag) { m_IsActive = flag; };
		Scene* GetScene() const { return m_Scene; };

	protected:
		void SetScene(Scene* scene);
		SpriteComponent* m_pSpriteComp = nullptr;
		CollisionComponent* m_pCollisionComp = nullptr;
		bool m_Attached = false;
	private:
		bool m_IsActive = true;
		Scene* m_Scene = nullptr;
	};
}

