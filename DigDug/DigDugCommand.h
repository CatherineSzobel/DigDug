#include "Command.h"
#include "InputComponent.h"
#include "PointsComponent.h"
#include "DigDugComponent.h"
#include "SpriteComponent.h"
#include "GameTime.h"
#include "servicelocator.h"
namespace dae
{
	class MoveLeftRightCommand final : public GameObjectCommand
	{
	public:
		MoveLeftRightCommand(GameObject* owner, int direction) : GameObjectCommand(owner), m_Direction{ direction }
		{
			m_pSpriteComp = GetGameActor()->GetComponent<SpriteComponent>();
			m_pDigDugComp = GetGameActor()->GetComponent<DigDugComponent>();
		};
		virtual ~MoveLeftRightCommand() = default;
		virtual void Execute() override
		{
			auto pos = GetGameActor()->GetLocalPosition();
			auto movementSpeed = GetGameActor()->GetComponent<InputComponent>()->GetMovementSpeed();
			auto elapsed = GameTime::GetInstance().GetDeltaTime();
			auto isDead = m_pDigDugComp->IsPlayerDeadCheck();
			auto isDigging = m_pDigDugComp->IsDigging();
			if (!isDead)
			{


				GetGameActor()->SetLocalPosition({ pos.x + ((movementSpeed * m_Direction) * elapsed) ,pos.y  , pos.z });
				//	m_OriginalPos = pos;
				if (m_Direction < 0)
				{
					if (isDigging)
						m_pSpriteComp->SetAnimationByName("PlayerMoveLeftWithArrow");
					else
						m_pSpriteComp->SetAnimationByName("PlayerWalkLeft");
				}
				else
				{
					if (isDigging)
						m_pSpriteComp->SetAnimationByName("PlayerMoveRightWithArrow");
					else
						m_pSpriteComp->SetAnimationByName("PlayerWalkRight");

				}
				m_pDigDugComp->SetMoving(true);
				m_pDigDugComp->SetUsingWaterPump(false);
			}
		}
		virtual void Undo() override
		{
			GetGameActor()->SetLocalPosition({ m_OriginalPos.x,m_OriginalPos.y,m_OriginalPos.z });
		}
	private:
		int m_Direction{};
		glm::vec3 m_OriginalPos{};
		SpriteComponent* m_pSpriteComp = nullptr;
		DigDugComponent* m_pDigDugComp = nullptr;
	};

	class MoveUpDownCommand final : public GameObjectCommand
	{
	public:
		MoveUpDownCommand(GameObject* owner, int direction) : GameObjectCommand{ owner }, m_Direction{ direction }
		{
			m_pSpriteComp = GetGameActor()->GetComponent<SpriteComponent>();
			m_pDigDugComp = GetGameActor()->GetComponent<DigDugComponent>();
		};
		virtual ~MoveUpDownCommand() = default;
		virtual void Execute() override
		{
			auto pos = GetGameActor()->GetLocalPosition();
			auto movementSpeed = GetGameActor()->GetComponent<InputComponent>()->GetMovementSpeed();
			auto elapsed = GameTime::GetInstance().GetDeltaTime();
			auto isDead = m_pDigDugComp->IsPlayerDeadCheck();
			auto isDigging = m_pDigDugComp->IsDigging();
			if (!isDead)
			{
				GetGameActor()->SetLocalPosition({ pos.x,pos.y + ((movementSpeed * m_Direction) * elapsed)  , pos.z });
				///	m_OriginalPos = pos;
				if (m_Direction < 0)
				{
					if (isDigging)
						m_pSpriteComp->SetAnimationByName("PlayerMoveUpWithArrow");
					else
						m_pSpriteComp->SetAnimationByName("PlayerWalkUp");

				}
				else
				{
					if (isDigging)
						m_pSpriteComp->SetAnimationByName("PlayerMoveDownWithArrow");
					else
						m_pSpriteComp->SetAnimationByName("PlayerWalkDown");
				}
				m_pDigDugComp->SetMoving(true);
				m_pDigDugComp->SetUsingWaterPump(false);
			}
		}
		virtual void Undo() override
		{
			GetGameActor()->SetLocalPosition({ m_OriginalPos.x,m_OriginalPos.y,m_OriginalPos.z });
		}
	private:
		int m_Direction{ };
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

				if (m_pSpriteComponent->GetCurrentAnimation() == "PlayerWalkLeft")
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
				m_pDigDugComp->SetMoving(false);
				m_pDigDugComp->SetUsingWaterPump(true);
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

