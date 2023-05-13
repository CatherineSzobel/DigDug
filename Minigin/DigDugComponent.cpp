#include "DigDugComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
dae::DigDugComponent::~DigDugComponent()
{
}

void dae::DigDugComponent::Render()
{
}

void dae::DigDugComponent::Update(float)
{
	IsPlayerDeadCheck();
	if (!m_IsDead)
	{

	}
	if (m_IsMoving && !servicelocator::get_sound_system().IsPlaying())
	{

		servicelocator::get_sound_system().PlayMusic("Sounds/Music/Theme.mp3",1, true);
	}
}

void dae::DigDugComponent::FixedUpdate(float)
{
}

void dae::DigDugComponent::Initialize()
{
	m_SpriteSheet = GetOwner()->GetComponent<SpriteComponent>();
	if (m_SpriteSheet == nullptr)
	{
		throw std::runtime_error(std::string("Current GameObject has no SpriteComponent. ") + SDL_GetError());
	}
	playerType = Player;
}

void dae::DigDugComponent::IsPlayerDeadCheck()
{
	if (GetLives() <= 0)
	{
		m_IsDead = true;
	}
}

int dae::DigDugComponent::GetLives() const
{
	return 0;
}
void dae::DigDugComponent::ResetDigger()
{
	m_IsDead = false;
}
