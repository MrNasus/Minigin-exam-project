#pragma once
#include <memory>

namespace minigin
{
	class Object;
	class BaseComponent
	{
	public:
		BaseComponent(const std::shared_ptr<Object>& object) { m_pObject = object; };
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Awake() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

	protected:

		std::shared_ptr<Object> m_pObject;
	};
}