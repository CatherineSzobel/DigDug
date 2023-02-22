#pragma once
namespace dae
{
	class BaseComponent
	{
	public:
		explicit BaseComponent() = default;
		~BaseComponent() = default;

		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;
		BaseComponent& operator= (const BaseComponent&) = delete;
		BaseComponent& operator= (const BaseComponent&&) = delete;


		//virtual void Initialize() = 0;
		virtual	void Render() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate(float deltaTime) = 0;
	};
}