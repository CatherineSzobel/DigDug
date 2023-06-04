#include "PointsComponent.h"
void digdug::PointsComponent::Render() {}

void digdug::PointsComponent::Update(float) {

}

void digdug::PointsComponent::FixedUpdate(float) {}

void digdug::PointsComponent::Notify(dae::GameObject* actor, Event event)
{
	switch (event)
	{
	case Event::OnPlayerDeath:
		m_CurrentPoints += 10;
		break;
	case Event::OnEnemyDeath:
		m_CurrentPoints += 20;
		break;
	case Event::IncreasePoints:
		m_CurrentPoints += 100;
		break;
	}
	actor->GetComponent<TextComponent>()->SetText("Points: " + std::to_string(m_CurrentPoints));
}
