#pragma once
#include "Observer.h"
#include <list>
namespace dae
{
	class Subject
	{
	public:
		Subject() = default;
		~Subject() = default;

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) noexcept = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) noexcept = delete;

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify( dae::GameObject* actor, Event event);
	private:
		std::list<Observer*> m_pObservers;
	};

}
