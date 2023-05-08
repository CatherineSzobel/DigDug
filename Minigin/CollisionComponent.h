#pragma once
#include "ExtraStructs.h"
class CollisionComponent
{
public:
	void CreateCollision(Rectf& collision);
	void CreateCollision(float left, float bottom, float width, float height);
	bool Collide(Rectf otherCollider);
	Rectf GetCollision() const { return m_Collision; };
	void SetCollision(bool flag) { m_IsEnabled = flag; };
	bool GetCollisionStatus() const { return m_IsEnabled; };
private:
	Rectf m_Collision;
	bool m_IsEnabled;
};

