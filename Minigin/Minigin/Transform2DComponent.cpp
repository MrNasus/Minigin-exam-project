#include "MiniginPCH.h"
#include "Transform2DComponent.h"
#include "Object.h"
#include "Structs.h"

Transform2DComponent::Transform2DComponent(Object* object)
	: BaseComponent(object)
	, m_pTransform(nullptr)
{
	m_pTransform = new Transform2D();
}

Transform2DComponent::~Transform2DComponent()
{
	delete m_pTransform;
	m_pTransform = nullptr;
}

const Transform2D& Transform2DComponent::GetTransform()
{
	return *m_pTransform;
}

const Position2D& Transform2DComponent::GetPosition()
{
	return m_pTransform->position;
}

const Scale2D& Transform2DComponent::GetScale()
{
	return m_pTransform->scale;
}

const Rotation2D& Transform2DComponent::GetRotation()
{
	return m_pTransform->rotation;
}

void Transform2DComponent::SetPosition(const Position2D& position)
{
	m_pTransform->position = position;
}

void Transform2DComponent::SetScale(const Scale2D& scale)
{
	m_pTransform->scale = scale;
}

void Transform2DComponent::SetRotation(const Rotation2D& rotation)
{
	m_pTransform->rotation = rotation;
}

void Transform2DComponent::SetTransform(const Transform2D& transform)
{
	*m_pTransform = transform;
}

