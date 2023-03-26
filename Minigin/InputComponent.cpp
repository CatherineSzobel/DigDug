#include "InputComponent.h"

void dae::InputComponent::Render()
{
}

void dae::InputComponent::Update(float)
{
}

void dae::InputComponent::FixedUpdate(float)
{
}

void dae::InputComponent::MoveUp()
{
	auto ownerObj = GetOwner();
	auto pos = ownerObj->GetLocalPosition();
	ownerObj->SetLocalPosition({ pos.x,pos.y + m_MovementSpeed , pos.z });
}

void dae::InputComponent::MoveLeft()
{
	auto ownerObj = GetOwner();
	auto pos = ownerObj->GetLocalPosition();
	ownerObj->SetLocalPosition({ pos.x - m_MovementSpeed,pos.y , pos.z });
}

void dae::InputComponent::MoveRight()
{
	auto ownerObj = GetOwner();
	auto pos = ownerObj->GetLocalPosition();
	ownerObj->SetLocalPosition({ pos.x + m_MovementSpeed,pos.y  , pos.z });
}

void dae::InputComponent::MoveDown()
{
	auto ownerObj = GetOwner();
	auto pos = ownerObj->GetLocalPosition();
	ownerObj->SetLocalPosition({ pos.x,pos.y - m_MovementSpeed , pos.z });
}
