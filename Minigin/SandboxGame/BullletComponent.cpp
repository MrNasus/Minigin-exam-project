#include "BullletComponent.h"
#include "Transform.h"
#include "Object.h"

using namespace minigin;

BullletComponent::BullletComponent(const std::weak_ptr<minigin::Object>& object, const minigin::Position2D& velocity, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_IsInUse{true}
	,m_Velocity{velocity}
{
}

void BullletComponent::Update(float deltaTime)
{
	if (m_IsInUse)
	{
		Transform t = m_pObject.lock()->GetTransform();
		Position2D p = t.GetPosition();
		p.x += m_Velocity.x * deltaTime;
		p.y += m_Velocity.y * deltaTime;
		t.SetPosition(p);
		m_pObject.lock()->SetTransform(t);
	}
}

void BullletComponent::Recycle(const minigin::Position2D& velocity, const minigin::Position2D& position)
{
	m_IsInUse = true;
	m_Velocity = velocity;
	Transform t = m_pObject.lock()->GetTransform();
	t.SetPosition(position);
	m_pObject.lock()->SetTransform(t);
}

void BullletComponent::Deactivate()
{
	m_IsInUse = false;
	Transform t = m_pObject.lock()->GetTransform();
	t.SetPosition(Position2D{-100.f, -100.f});
	m_pObject.lock()->SetTransform(t);
}
