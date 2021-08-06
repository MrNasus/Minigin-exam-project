#include "MiniginPCH.h"
#include "Object.h"
#include <algorithm>

Object::Object()
	: m_pComponents{}
{
}

void Object::AddComponent(BaseComponent* pNewComponent)
{
	if (!pNewComponent)
	{
		return;
	}

	for (auto* pComponent : m_pComponents)
	{
		if (pComponent == pNewComponent)
		{
			return;
		}
	}

	m_pComponents.push_back(pNewComponent);
}

void Object::RemoveComponent(BaseComponent* pComponent)
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

	pComponent->RemoveObject();
}

void Object::Awake()
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Awake();
	}
}

void Object::Start()
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Start();
	}
}

void Object::Update(float deltaTime)
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Update(deltaTime);
	}
}

void Object::LateUpdate(float deltaTime)
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->LateUpdate(deltaTime);
	}
}

void Object::Draw()
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Draw();
	}
}
