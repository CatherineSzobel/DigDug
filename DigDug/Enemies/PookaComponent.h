#pragma once
#include "BaseComponent.h"
#include "Enemy.h"
namespace dae
{

	class PookaComponent final : public BaseComponent
	{
	public:
		PookaComponent();
		virtual ~PookaComponent();
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;
		void MoveAround();
	private:
		SpriteComponent* m_pSpriteComp = nullptr;
		CollisionComponent* m_pCollisionComp = nullptr;
	};
}

