#include "BaseComponent.h"

void dae::BaseComponent::Initialize(GameObject* owner)
{
	m_pOwner = owner;
}
