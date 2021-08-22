#include "BulletComponent.h"
#include "Transform.h"
#include "Object.h"

using namespace minigin;

BulletComponent::BulletComponent(const std::weak_ptr<minigin::Object>& object, const minigin::Position2D& velocity, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_IsInUse{false}
	,m_Velocity{velocity}
	,m_Hitbox{}
{
	m_Hitbox = m_pObject.lock()->GetComponent<HitboxRectangleComponent>();
}

void BulletComponent::Update(float deltaTime)
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

const std::shared_ptr<minigin::HitboxRectangleComponent>& BulletComponent::GetHitbox() const
{
	return m_Hitbox;
}

void BulletComponent::Recycle(const minigin::Position2D& velocity, const minigin::Position2D& position)
{
	m_IsInUse = true;
	m_Velocity = velocity;
	Transform t = m_pObject.lock()->GetTransform();
	t.SetPosition(position);
	m_pObject.lock()->SetTransform(t);
}

void BulletComponent::Deactivate()
{
	m_IsInUse = false;
	Transform t = m_pObject.lock()->GetTransform();
	t.SetPosition(Position2D{-100.f, -100.f});
	m_pObject.lock()->SetTransform(t);
}

bool BulletComponent::IsInUse() const
{
	return m_IsInUse;
}
