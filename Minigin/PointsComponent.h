#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"
namespace dae
{
	class PointsComponent : public BaseComponent, public Observer
	{
	public:
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;

		// Inherited via Observer
		virtual void Notify(dae::GameObject* actor, Event event) override;

		int GetCurrentPoints() { return m_CurrentPoints; };
	private:
		int m_CurrentPoints;

	};

}

