#include "Subject.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_pObservers.emplace_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer));
}

void dae::Subject::Notify(GameObject* actor, Event event)
{
	for (auto& observer : m_pObservers)
	{
		observer->Notify(actor, event);
	}
}
