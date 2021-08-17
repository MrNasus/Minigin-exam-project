#include "MiniginPCH.h"
#include "Object.h"
#include <algorithm>

using namespace minigin;

Object::Object()
	: m_pComponents{}
	, m_Transform{}
{
}

const Transform& Object::GetTransform() const
{
	return m_Transform;
}

void Object::SetTransform(const Transform& transform)
{
	m_Transform = transform;
}

void Object::AddComponent(const std::shared_ptr<BaseComponent>& pNewComponent)
{
	if (!pNewComponent)
	{
		return;
	}

	for (std::shared_ptr<BaseComponent> pComponent : m_pComponents)
	{
		if (pComponent == pNewComponent)
		{
			return;
		}
	}

	m_pComponents.push_back(pNewComponent);
}

void Object::RemoveComponent(const std::shared_ptr<BaseComponent>& pComponent)
{
	if (!pComponent)
	{
		return;
	}

	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComponent);

	if (it == m_pComponents.end())
	{
		return;
	}

	m_pComponents.erase(it);
}

void Object::Awake()
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->Awake();
	}
}

void Object::Update(float deltaTime)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->Update(deltaTime);
	}
}


void Object::Render()
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}
