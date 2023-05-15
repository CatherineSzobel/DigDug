#pragma once
#include "ExtraStructs.h"
#include "BaseComponent.h"
#include "GameObject.h"
namespace dae
{
	class CollisionComponent final : public BaseComponent
	{
	public:
		CollisionComponent() = default;
		virtual ~CollisionComponent() = default;

		CollisionComponent(const CollisionComponent&) = delete;
		CollisionComponent(CollisionComponent&&) = delete;
		CollisionComponent& operator= (const CollisionComponent&) = delete;
		CollisionComponent& operator= (const CollisionComponent&&) = delete;

		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;


		void CreateCollision(const Rectf& collision, bool debug = false);
		void CreateCollision(float left, float bottom, float width, float height, bool debug = false);

		bool Collide( Rectf rect1);

		Rectf GetCollision() const { return m_Collision; };
		Rectf GetOtherCollision() const { return m_OtherPlayerCollision; };
		void SetCollision(bool flag) { m_IsEnabled = flag; };
		void SetOtherCollision(const Rectf& rect) { m_OtherPlayerCollision = rect; };
		bool GetCollisionStatus() const { return m_IsEnabled; };

		void DrawDebug(float left, float bottom, float width, float height);
	private:
		Rectf m_Collision, m_OtherPlayerCollision;
		bool m_IsEnabled = true, m_DebugOn = false;


	};

}

