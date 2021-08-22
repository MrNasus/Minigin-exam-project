#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include <vector>
#include <memory>

namespace minigin
{
	class Object
	{
	public:
		Object();
		virtual ~Object() = default;
		Object(const Object& other) = delete;
		Object(Object&& other) = delete;
		Object& operator=(const Object& other) = delete;
		Object& operator=(Object&& other) = delete;

		const Transform& GetTransform() const;
		void SetTransform(const Transform& transform);

		void AddComponent(const std::shared_ptr<BaseComponent>& pNewComponent);
		void RemoveComponent(const std::shared_ptr<BaseComponent>& pComponent);
		template <class T>
		std::shared_ptr<T> GetComponent()
		{
			const type_info& ti = typeid(T);
			for (std::shared_ptr<BaseComponent> component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
				{
					return std::static_pointer_cast<T, BaseComponent>(component);
				}
			}

			return nullptr;
		}

		template <class T>
		std::shared_ptr<T> GetComponent(const std::string& name)
		{
			for (std::shared_ptr<BaseComponent> component : m_pComponents)
			{
				if (component->GetName() == name)
				{
					return std::static_pointer_cast<T, BaseComponent>(component);
				}
			}

			return nullptr;
		}

		void Update(float deltaTime);
		void Render();
	protected:

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		Transform m_Transform;
	};
}