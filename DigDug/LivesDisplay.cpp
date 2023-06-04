#include "LivesDisplay.h"
void digdug::LivesDisplay::Notify(dae::GameObject* actor , Event event )
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

void digdug::LivesDisplay::Render()
{
}

void digdug::LivesDisplay::Update(float)
{
}

void digdug::LivesDisplay::FixedUpdate(float)
{
}
