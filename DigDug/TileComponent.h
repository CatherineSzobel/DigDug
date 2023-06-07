#include "BaseComponent.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "SpriteComponent.h"
#include "Helpers.h"
using namespace dae;
namespace digdug
{

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
		bool IsActive() const { return m_Active; };

	private:
		CollisionComponent* m_pCollisionComp = nullptr;
		float m_TileScale = 5.f;
		std::vector<Sprite*> m_pTileLists{};
		bool m_Active = true;
		SpriteComponent* m_pSpriteComp = nullptr;
	};
}

