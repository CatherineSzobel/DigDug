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
	private:
		SpriteComponent* m_pSpriteComp = nullptr;
		CollisionComponent* m_pCollisionComp = nullptr;
		bool m_IsFalling = false;
		float m_CurrentYPosition = 0.f;
	};

}

