#pragma once
#include <iostream>
#include "GameObject.h"
#include "InputComponent.h"
#include "HealthComponent.h"
#include "PointsComponent.h"
#include "DigDugComponent.h"
#include "SpriteComponent.h"
#include "GameTime.h"
#include "servicelocator.h"
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

	class MoveUpDownCommand final : public GameObjectCommand
	{
	public:
		MoveUpDownCommand(GameObject* owner, int direction) : GameObjectCommand{ owner }, m_Direction{ direction } {};
		virtual ~MoveUpDownCommand() = default;
		virtual void Execute() override
		{
			auto pos = GetGameActor()->GetLocalPosition();
			auto movementSpeed = GetGameActor()->GetComponent<InputComponent>()->GetMovementSpeed();
			auto elapsed = GameTime::GetInstance().GetDeltaTime();
			GetGameActor()->SetLocalPosition({ pos.x,pos.y + ((movementSpeed * m_Direction) * elapsed)  , pos.z });
			///	m_OriginalPos = pos;
			if (m_Direction < 0)
			{
				GetGameActor()->GetComponent<SpriteComponent>()->SetAnimationByName("PlayerWalkUp");

			}
			else
			{
				GetGameActor()->GetComponent<SpriteComponent>()->SetAnimationByName("PlayerWalkDown");
			}
			GetGameActor()->GetComponent<DigDugComponent>()->SetMoving(true);
		}
		virtual void Undo() override
		{
			GetGameActor()->SetLocalPosition({ m_OriginalPos.x,m_OriginalPos.y,m_OriginalPos.z });
		}
	private:
		int m_Direction{ };
		glm::vec3 m_OriginalPos{};
	};

	class MoveLeftRightCommand final : public GameObjectCommand
	{
	public:
		MoveLeftRightCommand(GameObject* owner, int direction) : GameObjectCommand(owner), m_Direction{ direction }
		{};
		virtual ~MoveLeftRightCommand() = default;
		virtual void Execute() override
		{
			auto pos = GetGameActor()->GetLocalPosition();
			auto movementSpeed = GetGameActor()->GetComponent<InputComponent>()->GetMovementSpeed();
			auto elapsed = GameTime::GetInstance().GetDeltaTime();

			GetGameActor()->SetLocalPosition({ pos.x + ((movementSpeed * m_Direction) * elapsed) ,pos.y  , pos.z });
			//	m_OriginalPos = pos;
			if (m_Direction < 0)
			{
				GetGameActor()->GetComponent<SpriteComponent>()->SetAnimationByName("PlayerWalkLeft");

			}
			else
			{
				GetGameActor()->GetComponent<SpriteComponent>()->SetAnimationByName("PlayerWalkRight");
			}
			GetGameActor()->GetComponent<DigDugComponent>()->SetMoving(true);
		}
		virtual void Undo() override
		{
			GetGameActor()->SetLocalPosition({ m_OriginalPos.x,m_OriginalPos.y,m_OriginalPos.z });
		}
	private:
		int m_Direction{};
		glm::vec3 m_OriginalPos{};
	};
	class KillCommand final : public GameObjectCommand
	{
	public:
		KillCommand(GameObject* owner) : GameObjectCommand(owner)
		{};
		virtual ~KillCommand() = default;
		virtual void Execute() override
		{
			GetGameActor()->GetComponent<HealthComponent>()->ForceDeath();
		}
		virtual void Undo() override
		{}
	private:
	};
	class IncreasePointsCommand final : public GameObjectCommand
	{
	public:
		IncreasePointsCommand(GameObject* owner) : GameObjectCommand(owner)
		{};
		virtual ~IncreasePointsCommand() = default;
		virtual void Execute() override
		{
			GetGameActor()->GetComponent<PointsComponent>()->Notify(GetGameActor(), Event::IncreasePoints);
		}
		virtual void Undo() override
		{}
	};
	class PlaySoundCommand final : public Command
	{
	public:
		PlaySoundCommand(std::string path, int volume) :m_Path{ path }, m_Volume{ volume }
		{
			auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + path;
			m_Path = fullPath;
		};
		virtual ~PlaySoundCommand() = default;
		virtual void Execute() override
		{
			auto& ss = servicelocator::get_sound_system();
			ss.Play(m_Path, m_Volume);
		}
		virtual void Undo() override
		{}
	private:
		std::string m_Path;
		int m_Volume;
	};
	class PlayMusicCommand final : public Command
	{
	public:
		PlayMusicCommand(std::string path, int volume) :m_Volume{ volume }
		{
			auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + path;
			m_Path = fullPath;
		};
		virtual ~PlayMusicCommand() = default;
		virtual void Execute() override
		{
			auto& ss = servicelocator::get_sound_system();
			ss.PlayMusic(m_Path, m_Volume);
		}
		virtual void Undo() override
		{
			//servicelocator::get_sound_system().PlaySoundA(0, 5);
		}
	private:
		std::string m_Path;
		int m_Volume;
	};
	class PumpCommand final : public GameObjectCommand
	{
	public:
		PumpCommand(GameObject* owner, std::string path, int volume)
			: GameObjectCommand(owner), m_Path{ path }, currentState {PlayerState::none}, m_Volume{ volume }
		{
			m_pSpriteComponent = GetGameActor()->GetComponent<SpriteComponent>();
		};
		virtual ~PumpCommand() = default;
		virtual void Execute() override
		{
			if (m_pSpriteComponent->GetCurrentAnimation()== "PlayerWalkLeft")
			{
				m_pSpriteComponent->SetAnimationByName("WaterPumpLeft");
			}
			else if (m_pSpriteComponent->GetCurrentAnimation() == "PlayerWalkRight")
			{
				m_pSpriteComponent->SetAnimationByName("WaterPumpRight");

			}
			else if (m_pSpriteComponent->GetCurrentAnimation() == "PlayerWalkUp")
			{
				m_pSpriteComponent->SetAnimationByName("WaterPumpUp");

			}
			else if (m_pSpriteComponent->GetCurrentAnimation() == "PlayerWalkDown")
			{
				m_pSpriteComponent->SetAnimationByName("WaterPumpDown");

			}
			servicelocator::get_sound_system().Play(m_Path, m_Volume);
			GetGameActor()->GetComponent<DigDugComponent>()->SetMoving(false);
			servicelocator::get_sound_system().HaltMusic();
		}
		virtual void Undo() override
		{}
	private:
		SpriteComponent* m_pSpriteComponent;
		enum class PlayerState
		{
			none,
			walkLeft,
			walkRight,
			walkUp,
			walkDown
		};
		PlayerState currentState;
		int m_Volume;
		std::string m_Path;
	};
}

