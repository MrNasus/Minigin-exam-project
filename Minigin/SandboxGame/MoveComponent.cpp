#include "MoveComponent.h"
#include "Object.h"

using namespace minigin;

MoveComponent::MoveComponent(const std::weak_ptr<Object>& object, const Position2D& speed, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_Speed{speed}
{
}

void MoveComponent::Update(float deltaTime)
{
	Transform transform = m_pObject.lock()->GetTransform();
	Position2D pos = transform.GetPosition();
	pos.x += m_Speed.x * deltaTime;
	pos.y += m_Speed.y * deltaTime;
	transform.SetPosition(pos);
	m_pObject.lock()->SetTransform(transform);
}
