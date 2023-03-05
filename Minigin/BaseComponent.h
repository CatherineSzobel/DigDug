#pragma once
namespace dae
{
	class GameObject;
	class BaseComponent
	{
		GameObject* m_pOwner;
	public:
		explicit BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;
		BaseComponent& operator= (const BaseComponent&) = delete;
		BaseComponent& operator= (const BaseComponent&&) = delete;

		virtual void Initialize();
		virtual	void Render() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float deltaTime) = 0;

		void SetOwner(GameObject* owner);
	protected:
		explicit BaseComponent(GameObject* pOwner) : m_pOwner(pOwner){}
		GameObject* GetOwner() const { return m_pOwner; };
	};
}