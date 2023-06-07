#include "PointComponent.h"
#include "TextComponent.h"
void digdug::PointComponent::Render() {}

void digdug::PointComponent::Update(float) {

}

void digdug::PointComponent::FixedUpdate(float) {}

void digdug::PointComponent::Notify(dae::GameObject* actor, Event event)
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
	}
	actor->GetComponent<TextComponent>()->SetText("Points: " + std::to_string(m_CurrentPoints));
}
