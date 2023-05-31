#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"
namespace dae
{
	class PumpComponent : public BaseComponent
	{
	public:
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;

		void Shoot(glm::vec2 playerPos);
		void Reset();
		bool IsAttached() { return m_Attached; }
	private:
		RenderComponent* m_pSpriteComp = nullptr;
		CollisionComponent* m_pCollisionComp = nullptr;
		float m_Speed, m_Lifetime = 2.f;
		bool m_Attached = false;
		glm::vec2 m_PlayerPosition;
	};

}

