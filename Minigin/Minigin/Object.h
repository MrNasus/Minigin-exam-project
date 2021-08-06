#pragma once
#include "BaseComponent.h"
#include <vector>

class Object
{
public:
	Object();
	virtual ~Object() = default;
	Object(const Object & other) = delete;
	Object(Object && other) = delete;
	Object& operator=(const Object & other) = delete;
	Object& operator=(Object && other) = delete;

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
	void Start();
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw();
protected:

private:
	std::vector<BaseComponent*> m_pComponents;
};