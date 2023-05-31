#pragma once
#include "GameObject.h"
#include <string>
#include "Event.h"
namespace dae
{
	class Observer 
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer& other) = default;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void Notify(dae::GameObject* actor, Event event) = 0;
	private:

	};
}
