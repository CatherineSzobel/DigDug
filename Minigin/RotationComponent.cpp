#include "RotationComponent.h"
#include "GameObject.h"

void dae::RotationComponent::Initialize()
{
	m_Center = GetOwner()->GetLocalPosition();
}
void dae::RotationComponent::Render(){}

void dae::RotationComponent::Update(float deltaTime )
{
	m_CurrentRotation = m_RotationSpeed * deltaTime;

	//incomplete...
}

void dae::RotationComponent::FixedUpdate(float){}
