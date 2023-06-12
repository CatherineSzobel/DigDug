#include "LivesDisplay.h"
void digdug::LivesDisplay::Notify(Event event)
{
	if (Event::OnPlayerDeath == event)
	{
		GetOwner()->GetComponent<dae::SpriteComponent>()->IncreaseSpriteFrame();
	}
	else if (event == Event::OnGameOver)
	{
		GetOwner()->GetComponent<dae::SpriteComponent>()->GetCurrentSprite()->SetCurrentFrame(3);
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
	GetOwner()->AddComponent<dae::SpriteComponent>()->Initialize();
	GetOwner()->GetComponent<dae::SpriteComponent>()->AddAnimationStrips("Sprites/livesSprite.png", 4, 1, 4.f, 1.f, "lives", true);
	GetOwner()->GetComponent<dae::SpriteComponent>()->SetAnimationByName("lives");
}
