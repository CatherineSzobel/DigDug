#include "PointComponent.h"
#include "TextComponent.h"
#include "LevelManager.h"
#include "Game.h"
void digdug::PointComponent::Render() {}

void digdug::PointComponent::Update(float) {

}

void digdug::PointComponent::FixedUpdate(float) {}

void digdug::PointComponent::Notify( Event event)
{
	switch (event)
	{
	case Event::OnPookaFirstLayerDeath:
		m_CurrentPoints += 200;
		break;
	case Event::OnPookaSecondLayerDeath:
		m_CurrentPoints += 300;
		break;
	case Event::OnPookaThirdLayerDeath:
		m_CurrentPoints += 400;
		break;
	case Event::OnPookaFourthLayerDeath:
		m_CurrentPoints += 500;
		break;
	case Event::OnFygarFirstLayerDeath:
		m_CurrentPoints += 400;
		break;
	case Event::OnFygarSecondLayerDeath:
		m_CurrentPoints += 600;
		break;
	case Event::OnFygarThirdLayerDeath:
		m_CurrentPoints += 800;
		break;
	case Event::OnFygarFourthLayerDeath:
		m_CurrentPoints += 1000;
		break;
	case Event::OnDeathByRock:
		m_CurrentPoints += 1000;
		break;
	}
	GetOwner()->GetComponent<TextComponent>()->SetText(std::to_string(m_CurrentPoints));
	LevelManager levelmanager;
	levelmanager.SaveHighScoreInFile(m_CurrentPoints);
	Game::GetInstance().SetCurrentPoints(m_CurrentPoints);
}
