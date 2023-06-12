#pragma once
#include "BaseComponent.h"
#include "Enemy.h"
namespace digdug
{
	class Enemy;
	class FygarsComponent final : public dae::BaseComponent, public Enemy
	{
	public:
		FygarsComponent() = default;
		virtual ~FygarsComponent();
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;

		// Inherited via Enemy
		virtual void Release() override;
	private:

	
	};
}


