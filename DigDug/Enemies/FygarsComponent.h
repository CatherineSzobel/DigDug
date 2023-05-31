#pragma once
#include "BaseComponent.h"

#include "Enemy.h"
namespace dae
{
	class Enemy;
	class FygarsComponent final : public BaseComponent, public Enemy
	{
	public:
		FygarsComponent() = default;
		virtual ~FygarsComponent();
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;
	private:
	};
}


