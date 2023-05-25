#include "Enemy.h"
namespace dae
{
	class FygarsComponent final : public BaseComponent
	{
	public:
		FygarsComponent() = default;
		virtual ~FygarsComponent();
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;
	private:
		SpriteComponent* m_pSpriteComp = nullptr;
		CollisionComponent* m_pCollisionComp = nullptr;
	};
}


