#pragma once
#include "GameObject.h"
namespace dae
{
	class State
	{
	public:
		State() = default;
		virtual ~State() = default;
		virtual void OnEnter(dae::GameObject*) {};
	};
}


