#pragma once
#include "BaseComponent.h"
#include "Enemy.h"
using namespace dae;
namespace digdug
{

	class PookaComponent final : public BaseComponent, public Enemy
	{
	public:
		PookaComponent();
		virtual ~PookaComponent();
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Initialize() override;
		void MoveAround();
	private:
		bool m_IsInvinsible = false;
	};
}

