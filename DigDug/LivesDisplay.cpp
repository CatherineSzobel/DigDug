#include "LivesDisplay.h"
void dae::LivesDisplay::Notify(dae::GameObject* actor , Event event )
{
	if (Event::OnPlayerDeath == event)
	{
		actor->GetComponent<SpriteComponent>()->IncreaseSpriteFrame();
	}
	else if (event == Event::OnGameOver)
	{
		actor->GetComponent<SpriteComponent>()->GetCurrentSprite()->SetCurrentFrame(3);
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
