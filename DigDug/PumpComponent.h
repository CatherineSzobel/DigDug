#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "Enemy.h"
using namespace dae;
namespace digdug
{
	class PumpComponent final: public BaseComponent
	{
	public:
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;

		void Shoot(glm::vec2 playerPos);
		void Pump();
		void Reset();
		bool IsAttached() { return m_Attached; }
		Rectf GetCollision() const;
		Enemy* GetEnemyPointer() const { return m_Enemy; };
	private:
		RenderComponent* m_pSpriteComp = nullptr;
		CollisionComponent* m_pCollisionComp = nullptr;

		CollisionManager m_CollisionManager;
		bool m_Attached = false, m_IsActive = false;
		float m_Speed, m_Lifetime = 2.f,m_MaxStretch = 50.f;
		const float m_PumpSpeed = 15.f;
		int m_CurrentPump = 0;
		const int m_MaxPump = 2;
		glm::vec2 m_PlayerPosition;
		glm::vec2 m_PumpSize;
		bool m_HasShot{ false };
		Enemy* m_Enemy;
		std::vector<std::string> m_pListOfArrowRenders{};
	};

}

