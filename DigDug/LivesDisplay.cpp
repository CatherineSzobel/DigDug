#include "LivesDisplay.h"
void dae::LivesDisplay::Notify(dae::GameObject* actor , Event event )
{
	if (Event::OnPlayerDeath == event)
	{
		auto sprite = actor->GetComponent<SpriteComponent>()->GetCurrentSprite();
		actor->GetComponent<SpriteComponent>()->SetFrameSize(sprite->GetWidth() - (sprite->GetFrameWidth() * currentLives), sprite->GetHeight());

	}
	else if (event == Event::OnGameOver)
	{
		actor->GetComponent<SpriteComponent>()->SetFrameSize(0.f,0.f);
	}

}
