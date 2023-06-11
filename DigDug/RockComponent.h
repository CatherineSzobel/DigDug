#include "BaseComponent.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
using namespace dae;
namespace digdug
{
	class RockComponent final : public BaseComponent
	{
	public:
		RockComponent() = default;
		virtual ~RockComponent();
		RockComponent(const RockComponent& other) = delete;
		RockComponent(RockComponent&& other) noexcept = delete;
		RockComponent& operator=(const RockComponent& other) = delete;
		RockComponent& operator=(RockComponent&& other) noexcept = delete;

		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;
		void MoveDown(float elapsed);
		void DeletionCountdown(float elapsed);
	private:
		SpriteComponent* m_pSpriteComp = nullptr;
		CollisionComponent* m_pCollisionComp = nullptr;
		bool m_IsFalling = false, m_HasFallen = false;
		float m_CurrentTime = 0.f, m_MaxDeletionTimer = 1.f, m_MaxWaitTimeToFall = 1.f;
		bool m_WaitTimerFinished = false, m_DeletionWaitTimeFinished = false;
		float m_Speed = 15.f;
		float m_CurrentYPosition = 0.f;
		CollisionComponent* m_pSandCollision = nullptr;
	};

}

