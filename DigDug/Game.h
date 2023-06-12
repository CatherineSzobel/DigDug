#pragma once
#include "Singleton.h"
#include <string>
class Game final : public dae::Singleton<Game>
{
public:
	bool IsPlayerDead()const { return m_IsPlayerDead; }
	bool IsBothPlayerDead() const { return m_IsBothPlayerDead; };

	void SetPlayerDead(bool flag) { m_IsPlayerDead = flag; };
	void SetBothPlayerDead(bool flag) { m_IsBothPlayerDead = flag; }

	int GetCurrentPoints() const { return m_CurrentPoints; }
	void SetCurrentPoints(int points) { m_CurrentPoints = points; };

	float GetWorldWidth() { return m_WorldWidth; };
	float GetWorldHeight() { return m_WorldHeight; };

	std::string GetGameMode() { return m_GameMode; };
	void SetGameMode(std::string mode) { m_GameMode = mode; };

	int PlayerLeft() const { return m_PlayerLeft; }
	void DecreasePlayerLeft() { --m_PlayerLeft; };
	void ResetPlayer() { m_PlayerLeft = 2; };
private:
	std::string m_GameMode;
	bool m_IsPlayerDead = false;
	bool m_IsBothPlayerDead = false;
	int m_CurrentPoints = 0;
	int m_PlayerLeft = 2;
	const float m_WorldHeight = 480;
	const float m_WorldWidth = 640;
};

