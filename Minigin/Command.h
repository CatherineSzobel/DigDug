#pragma once
#include <iostream>
#include "GameObject.h"

namespace dae
{
	class Command
	{
	public:
		Command() {};
		virtual ~Command() = default;
		virtual void Execute() = 0;
		virtual void Undo() = 0;
	};

	class GameObjectCommand : public Command
	{
	protected:
		GameObject* GetGameActor() { return m_GameActor; }
	public:
		GameObjectCommand(GameObject* owner)
			:m_GameActor{ owner }
		{};
		virtual ~GameObjectCommand() = default;
		virtual void Execute() = 0;
		virtual void Undo() = 0;
	private:
		GameObject* m_GameActor{};
	};
}

