#pragma once
#include "BaseComponent.h"
#include "CollisionComponent.h"
namespace dae
{

	class TileComponent final : public BaseComponent
	{
	public:
		TileComponent() = default;
		virtual ~TileComponent() = default;

		TileComponent(const TileComponent&) = delete;
		TileComponent(TileComponent&&) = delete;
		TileComponent& operator= (const TileComponent&) = delete;
		TileComponent& operator= (const TileComponent&&) = delete;

		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;
	private:
		CollisionComponent* m_pCollisionComp = nullptr;
	};
}

