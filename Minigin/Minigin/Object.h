#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include <vector>

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

		void AddComponent(BaseComponent* pNewComponent);
		void RemoveComponent(BaseComponent* pComponent);
		template <class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
				{
					return static_cast<T*>(component);
				}
			}

			return nullptr;
		}

		void Awake();
		void Update(float deltaTime);
		void Render();
	protected:

	private:
		std::vector<BaseComponent*> m_pComponents;
		Transform m_Transform;
	};
}