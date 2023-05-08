#include "CollisionComponent.h"

void CollisionComponent::CreateCollision(Rectf& collision)
{
	m_Collision = collision;
}

void CollisionComponent::CreateCollision(float left, float bottom, float width, float height)
{
	m_Collision = Rectf(left, bottom, width, height);
}

bool CollisionComponent::Collide(Rectf)
{
	return false;
}
