#pragma once
#include "Singleton.h"
class Game : public dae::Singleton<Game>
{
public:
	bool IsPlayerDead()const { return m_IsPlayerDead; }
	void SetPlayerDead(bool flag) { m_IsPlayerDead = flag; };

	int GetCurrentPoints() const { return m_CurrentPoints; }
	void SetCurrentPoints(int points) { m_CurrentPoints = points; };

	float GetWorldWidth() { return m_WorldWidth; };
	float GetWorldHeight() { return m_WorldHeight; };
private:
	bool m_IsPlayerDead = false;
	int m_CurrentPoints = 0;
	const float m_WorldHeight = 480;
	const float m_WorldWidth = 640;
};

