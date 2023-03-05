#include "BaseComponent.h"
#include "GameObject.h"
void dae::BaseComponent::SetOwner(GameObject* owner)
{
	if (!owner)
	{
		return;
	}
	m_pOwner = owner;
}

void dae::BaseComponent::Initialize(){}
