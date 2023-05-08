#pragma once
#include "ExtraStructs.h"
class CollisionComponent
{
public:
	void CreateCollision(Rectf& collision);
	void CreateCollision(float left, float bottom, float width, float height);
	Rectf GetCollision() {return m_Collision;};
private:
	Rectf m_Collision;
};

