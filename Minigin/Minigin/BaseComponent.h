#pragma once
#include <memory>
#include <string>

namespace minigin
{
	class Object;
	class BaseComponent
	{
	public:
		BaseComponent(const std::shared_ptr<Object>& object, const std::string& name) { m_pObject = object; m_Name = name; };
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Awake() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		const std::string& GetName() const { return m_Name; };
	protected:

		std::string m_Name;
		std::shared_ptr<Object> m_pObject;
	};
}