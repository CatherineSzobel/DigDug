#include "LivesDisplay.h"
void dae::LivesDisplay::Notify(dae::GameObject* actor , Event event )
{
	if (Event::OnPlayerDeath == event)
	{
		--currentLives;
		auto sprite = actor->GetComponent<SpriteComponent>()->GetCurrentSprite();
		auto width = (sprite->GetFrameWidth() * currentLives) - sprite->GetWidth();
		auto height = sprite->GetHeight();
		actor->GetComponent<SpriteComponent>()->SetFrameSize(width, height);

	}
	else if (event == Event::OnGameOver)
	{
		actor->GetComponent<SpriteComponent>()->SetFrameSize(0.f,0.f);
	}

}

void dae::LivesDisplay::Render()
{
}

void dae::LivesDisplay::Update(float)
{
}

void dae::LivesDisplay::FixedUpdate(float)
{
}
