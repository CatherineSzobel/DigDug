#include "Subject.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_pObservers.emplace_front(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	auto observerIt = std::find(m_pObservers.cbegin(), m_pObservers.cend(), observer);
	if (observerIt != m_pObservers.cend())
	{
		m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer));
	}
}

void dae::Subject::Notify( dae::GameObject* actor, Event event)
{
	for (const auto& observer : m_pObservers)
	{
		observer->Notify(actor, event);
	}
}
