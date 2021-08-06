#pragma once
#include "BaseComponent.h"

struct Position2D;
struct Scale2D;
struct Transform2D;
struct Rotation2D;
class Transform2DComponent : public BaseComponent
{
public:
	Transform2DComponent(Object* object);
	virtual ~Transform2DComponent();
	Transform2DComponent(const Transform2DComponent & other) = delete;
	Transform2DComponent(Transform2DComponent && other) = delete;
	Transform2DComponent& operator=(const Transform2DComponent & other) = delete;
	Transform2DComponent& operator=(Transform2DComponent && other) = delete;

	virtual const Transform2D& GetTransform();
	virtual const Position2D& GetPosition();
	virtual const Scale2D& GetScale();
	virtual const Rotation2D& GetRotation();

	virtual void SetPosition(const Position2D& position);
	virtual void SetScale(const Scale2D& scale);
	virtual void SetRotation(const Rotation2D& rotation);
	virtual void SetTransform(const Transform2D& transform);

protected:
	Transform2D* m_pTransform;
};