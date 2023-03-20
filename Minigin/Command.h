#pragma once
#include <iostream>
#include "GameActor.h"
namespace dae
{
	class Command
	{
	//protected:
	//	GameActor* GetGameActor() { return m_GameActor; }
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	//private:
	//	GameActor* m_GameActor{};
	};

	class FireCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Fire!"; }
	};

	class JumpCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Jump!"; }
	};

	class DuckCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Duck!"; }
	};

	class FartCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Fart!"; }
	};
}

