#pragma once
#include "BaseComponent.h"
#include "TransformStruct.h"

namespace minigin
{
	class Transform
	{
	public:
		Transform();
		virtual ~Transform();
		Transform(const Transform& other);
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other);
		Transform& operator=(Transform&& other) = delete;

		virtual const Transform2D& GetTransform() const;
		virtual const Position2D& GetPosition() const;
		virtual const Scale2D& GetScale() const;
		virtual const Rotation2D& GetRotation() const;

		virtual void SetPosition(const Position2D& position);
		virtual void SetScale(const Scale2D& scale);
		virtual void SetRotation(const Rotation2D& rotation);
		virtual void SetTransform(const Transform2D& transform);

	protected:
		Transform2D m_Transform;
	};
}