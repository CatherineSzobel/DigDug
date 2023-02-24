#pragma once
namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		explicit BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;
		BaseComponent& operator= (const BaseComponent&) = delete;
		BaseComponent& operator= (const BaseComponent&&) = delete;


		virtual void Initialize(GameObject* owner);
		virtual	void Render() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float deltaTime) = 0;
	protected:
		GameObject* m_pOwner;
	};
}