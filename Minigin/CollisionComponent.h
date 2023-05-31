#pragma once
#include "ExtraStructs.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "Scene.h"
namespace dae
{
	class CollisionComponent final : public BaseComponent
	{
	public:
		CollisionComponent();
		virtual ~CollisionComponent() = default;

		CollisionComponent(const CollisionComponent&) = delete;
		CollisionComponent(CollisionComponent&&) = delete;
		CollisionComponent& operator= (const CollisionComponent&) = delete;
		CollisionComponent& operator= (const CollisionComponent&&) = delete;

		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;


		void CreateCollision(const Rectf& collision, CollisionType type, bool debug = false);
		void CreateCollision(float left, float bottom, float width, float height, CollisionType type, bool debug = false);

		bool Collide( Rectf rect1);

		void SetCollision(bool flag) { m_IsEnabled = flag; };
		void SetCollisionType(CollisionType type) { m_CollisionType = type; };

		Rectf GetCollision() const { return m_Collision; };
		bool GetCollisionStatus() const { return m_IsEnabled; };
		CollisionType GetCollisionType() { return m_CollisionType; };
		Scene* GetScene() {return m_Scene;};

		void DrawDebug(float left, float bottom, float width, float height);
	private:
		Rectf m_Collision, m_OriginalCollisionPosition;
		bool m_IsEnabled = true, m_DebugOn = false;
		CollisionType m_CollisionType;
		Scene* m_Scene;

		void SetScene(Scene* scene);
	};

}

