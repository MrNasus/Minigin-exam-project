#include "MoveComponent.h"
#include "Object.h"

MoveComponent::MoveComponent(const std::shared_ptr<Object>& object, const Position2D& speed)
	:BaseComponent(object)
	,m_Speed{speed}
{
}

void MoveComponent::Update(float deltaTime)
{
	Transform transform = m_pObject->GetTransform();
	Position2D pos = transform.GetPosition();
	pos.x += m_Speed.x * deltaTime;
	pos.y += m_Speed.y * deltaTime;
	transform.SetPosition(pos);
	m_pObject->SetTransform(transform);
}
