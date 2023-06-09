#include "BaseComponent.h"
#include "Observer.h"
using namespace dae;
namespace digdug
{
	class PointComponent final : public BaseComponent, public Observer
	{
	public:
		// Inherited via BaseComponent
		virtual void Render() override;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;

		// Inherited via Observer
		virtual void Notify( Event event) override;

		int GetCurrentPoints() { return m_CurrentPoints; };
	private:
		int m_CurrentPoints;

	};

}

