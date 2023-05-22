#include "BaseComponent.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "SpriteComponent.h"
namespace dae
{
	enum class TileType
	{
		YellowSand,
		OrangeSand,
		BrownSand,
		RedSand
	};
	class TileComponent final : public BaseComponent
	{
	public:
		TileComponent();
		virtual ~TileComponent();

		TileComponent(const TileComponent&) = delete;
		TileComponent(TileComponent&&) = delete;
		TileComponent& operator= (const TileComponent&) = delete;
		TileComponent& operator= (const TileComponent&&) = delete;

		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;

		void SetSandType(TileType tileType);

	private:
		CollisionComponent* m_pCollisionComp = nullptr;
		float m_TileScale = 5.f;
		std::vector<Sprite*> m_pTileLists{};
		SpriteComponent* m_pSpriteComp = nullptr;
	};
}

