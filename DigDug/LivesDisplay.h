#pragma once
#include "SpriteComponent.h"
#include "Observer.h"
namespace dae
{
	class LivesDisplay final : public Observer
	{
	public:

		virtual void Notify(dae::GameObject* actor, Event event) override;
		void SetCurrentLives(int lives) { currentLives = lives; };
	private:
		SpriteComponent* m_pSpriteComp;
		int currentLives;
	};

}

