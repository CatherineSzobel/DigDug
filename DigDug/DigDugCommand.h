#pragma once
#include "Command.h"
#include "InputComponent.h"
#include "DigDugComponent.h"
#include "GameTime.h"
#include "servicelocator.h"
#include "SceneManager.h"
#include "ExtraStructs.h"
#include "UIComponent.h"
using namespace dae;
namespace digdug
{
	class MoveCommand final : public GameObjectCommand
	{
	public:

		MoveCommand(GameObject* owner, Direction direction) : GameObjectCommand{ owner }, m_Direction{ direction }
		{
			m_pSpriteComp = GetGameActor()->GetComponent<SpriteComponent>();
			m_pDigDugComp = GetGameActor()->GetComponent<DigDugComponent>();

		};
		virtual ~MoveCommand() = default;
		virtual void Execute() override
		{
			auto pos = GetGameActor()->GetLocalPosition();
			auto elapsed = GameTime::GetInstance().GetDeltaTime();
			auto isDead = m_pDigDugComp->IsPlayerDeadCheck();
			auto isGameOver = GetGameActor()->GetComponent<HealthComponent>()->GetIsGameOver();
			m_OriginalSpeed = GetGameActor()->GetComponent<InputComponent>()->GetMovementSpeed();
			m_MovementSpeed = m_OriginalSpeed;
			if (!isGameOver)
			{
				if (!isDead)
				{
					///	m_OriginalPos = pos;
					switch (m_Direction)
					{
					case Direction::left:
						m_DirectionVec.x = -1;
						m_DirectionVec.y = 0;
						break;
					case Direction::right:
						m_DirectionVec.x = 1;
						m_DirectionVec.y = 0;
						break;
					case Direction::up:
						m_DirectionVec.y = -1;
						m_DirectionVec.x = 0;
						break;
					case Direction::down:
						m_DirectionVec.y = 1;
						m_DirectionVec.x = 0;
						break;
					}
					m_pDigDugComp->SetDirection(m_Direction);
					Clamp();
					GetGameActor()->SetLocalPosition({ pos.x + ((m_MovementSpeed * m_DirectionVec.x) * elapsed),pos.y + ((m_MovementSpeed * m_DirectionVec.y) * elapsed)  , pos.z });
					m_pDigDugComp->SetMoving(true);
					//m_pDigDugComp->SetUsingWaterPump(false);
				}
			}
		}
		virtual void Undo() override
		{
			GetGameActor()->SetLocalPosition({ m_OriginalPos.x,m_OriginalPos.y,m_OriginalPos.z });
		}
		void Clamp()
		{
			auto playerPosition = glm::vec2{ GetGameActor()->GetLocalPosition().x + GetGameActor()->GetComponent<SpriteComponent>()->GetSpriteSize().x,
			GetGameActor()->GetLocalPosition().y + GetGameActor()->GetComponent<SpriteComponent>()->GetSpriteSize().y };

			glm::vec2 levelBoundaryRow = { 70.f, 452.f };
			glm::vec2 levelBoundaryColumm = { 0.f, Game::GetInstance().GetWorldWidth() };

			if (playerPosition.x - GetGameActor()->GetComponent<SpriteComponent>()->GetSpriteSize().x <= levelBoundaryColumm.x && m_Direction == Direction::left ||
				playerPosition.x >= levelBoundaryColumm .y && m_Direction == Direction::right ||
				playerPosition.y - GetGameActor()->GetComponent<SpriteComponent>()->GetSpriteSize().y <= levelBoundaryRow.x && m_Direction == Direction::up ||
				playerPosition.y >= levelBoundaryRow.y && m_Direction == Direction::down)
			{
				m_MovementSpeed = 0.f;
			}
			else
			{
				m_MovementSpeed = m_OriginalSpeed;
			}
		};
	private:
		Direction m_Direction{ };
		float m_MovementSpeed{}, m_OriginalSpeed{};
		glm::vec2 m_DirectionVec{};
		glm::vec3 m_OriginalPos{};
		SpriteComponent* m_pSpriteComp = nullptr;
		DigDugComponent* m_pDigDugComp = nullptr;
	};
	class PumpCommand final : public GameObjectCommand
	{
	public:
		PumpCommand(GameObject* owner, std::string path, int volume)
			: GameObjectCommand(owner), m_Path{ path }, m_Volume{ volume }
		{
			m_pSpriteComponent = GetGameActor()->GetComponent<SpriteComponent>();
			m_pDigDugComp = GetGameActor()->GetComponent<DigDugComponent>();
		};
		virtual ~PumpCommand() = default;
		virtual void Execute() override
		{
			if (!GetGameActor()->GetComponent<DigDugComponent>()->IsPlayerDeadCheck())
			{
				m_pDigDugComp->SetUsingWaterPump(true);
				auto isThrown = m_pDigDugComp->IsThrown();
				if (isThrown)
				{
					servicelocator::get_sound_system().Play(m_Path, m_Volume);
				}
				else
				{
					//	servicelocator::get_sound_system().Play("Sounds/Sound/PumpingSound.wav", m_Volume);
				}
				m_pDigDugComp->SetMoving(false);
				servicelocator::get_sound_system().HaltMusic();

			}
		}
		virtual void Undo() override
		{}
	private:
		SpriteComponent* m_pSpriteComponent;
		DigDugComponent* m_pDigDugComp = nullptr;
		int m_Volume;
		std::string m_Path;
	};

	class NextSceneCommand final : public Command
	{
	public:
		NextSceneCommand() {};
		virtual ~NextSceneCommand() = default;
		virtual void Execute() override;
		virtual void Undo() override {};
	private:

	};
	class HandleUpDownMenuCommand final : public GameObjectCommand
	{
	public:
		HandleUpDownMenuCommand(GameObject* owner, Direction direction)
			:GameObjectCommand{ owner }, m_direction{ direction }, m_MinimumUpwards{ 299.f }, m_MaximumDownwards{ 331.f }
		{

		};
		virtual ~HandleUpDownMenuCommand() = default;
		virtual void Execute() override
		{
			m_originalPosition = GetGameActor()->GetLocalPosition();
			float currentOffSet = 0;
			const float offSet = 30.f;
			switch (m_direction)
			{
			case Direction::up:
				GetGameActor()->GetComponent<UIComponent>()->HandleAction(-1);
				currentOffSet = -offSet;
				break;
			case Direction::down:
				GetGameActor()->GetComponent<UIComponent>()->HandleAction(1);
				currentOffSet = offSet;
				break;
			}
			auto newPosition = m_originalPosition.y + currentOffSet;
			if (newPosition < m_MinimumUpwards)
			{
				currentOffSet = offSet;
			}
			if (newPosition > m_MaximumDownwards)
			{
				currentOffSet = -offSet;
			}

			GetGameActor()->SetLocalPosition({ m_originalPosition.x,m_originalPosition.y + currentOffSet,m_originalPosition.z });
		};
		virtual void Undo() override
		{};
	private:
		Direction m_direction;
		glm::vec3 m_originalPosition;
		float m_MinimumUpwards;
		float m_MaximumDownwards;
	};
	class HandleMenuCommand final : public GameObjectCommand
	{
	public:
		HandleMenuCommand(GameObject* owner)
			:GameObjectCommand(owner)
		{
		};
		virtual ~HandleMenuCommand() = default;
		virtual void Execute() override
		{
			auto gb = GetGameActor()->GetComponent<InputComponent>();
			if (gb != nullptr)
			{
				m_Action = GetGameActor()->GetComponent<UIComponent>()->GetAction();
				GetGameActor()->GetComponent<UIComponent>()->ActivateAction(m_Action);
				GetGameActor()->RemoveComponent<InputComponent>();
				GetGameActor()->RemoveComponent<RenderComponent>();
				GetGameActor()->SetLocalPosition(glm::vec3{ 220.f,50.f,0.f });
			}


		};
		virtual void Undo() override
		{};
	private:
		std::string m_Action;
	};
	//class KillCommand final : public GameObjectCommand
	//{
	//public:
	//	KillCommand(GameObject* owner) : GameObjectCommand(owner)
	//	{
	//		m_pSpriteComponent = GetGameActor()->GetComponent<SpriteComponent>();
	//		m_pDigDugComp = GetGameActor()->GetComponent<DigDugComponent>();
	//	};
	//	virtual ~KillCommand() = default;
	//	virtual void Execute() override
	//	{
	//		auto digdugComp = GetGameActor()->GetComponent<DigDugComponent>();
	//		auto healthcomp = GetGameActor()->GetComponent<HealthComponent>();
	//		healthcomp->ForceDeath();
	//		if (healthcomp->GetLives() > 0 && digdugComp != nullptr)
	//		{
	//			servicelocator::get_sound_system().Play("Sounds/Sound/GetHitSound.wav", 2);
	//			m_pDigDugComp->SetMoving(false);
	//			m_pDigDugComp->SetDeath(true);
	//			servicelocator::get_sound_system().HaltMusic();
	//		}
	//	}
	//	virtual void Undo() override
	//	{}
	//private:
	//	SpriteComponent* m_pSpriteComponent;
	//	DigDugComponent* m_pDigDugComp = nullptr;
	//};

}

