#pragma once
#include "GameObject.h"
#include <string>
#include "Event.h"
namespace dae
{
	//template class
	class Observer 
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer& other) = default;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void Notify(Event event) = 0;
	private:

	};
}
