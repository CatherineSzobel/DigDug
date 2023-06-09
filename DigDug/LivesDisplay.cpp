#include "LivesDisplay.h"
void digdug::LivesDisplay::Notify(Event event)
{
	if (Event::OnPlayerDeath == event)
	{
		GetOwner()->GetComponent<SpriteComponent>()->IncreaseSpriteFrame();
	}
	else if (event == Event::OnGameOver)
	{
		GetOwner()->GetComponent<SpriteComponent>()->GetCurrentSprite()->SetCurrentFrame(3);
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

void digdug::LivesDisplay::Initialize()
{
	GetOwner()->AddComponent<SpriteComponent>()->Initialize();
	GetOwner()->GetComponent<SpriteComponent>()->AddAnimationStrips("Sprites/livesSprite.png", 4, 1, 4.f, 1.f, "lives", true);
	GetOwner()->GetComponent<SpriteComponent>()->SetAnimationByName("lives");
}
