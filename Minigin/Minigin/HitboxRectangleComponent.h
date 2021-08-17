#pragma once
#include "BaseComponent.h"
#include "HitboxStruct.h"
#include "TransformStruct.h"

namespace minigin
{
	class HitboxRectangleComponent : public BaseComponent
	{
		HitboxRectangleComponent(const std::shared_ptr<Object>& object);
		HitboxRectangleComponent(const std::shared_ptr<Object>& object, float width, float height);
		HitboxRectangleComponent(const std::shared_ptr<Object>& object, float width, float height, float offsetX, float offsetY);
		virtual ~HitboxRectangleComponent() = default;
		HitboxRectangleComponent(const HitboxRectangleComponent& other) = delete;
		HitboxRectangleComponent(HitboxRectangleComponent&& other) = delete;
		HitboxRectangleComponent& operator=(const HitboxRectangleComponent& other) = delete;
		HitboxRectangleComponent& operator=(HitboxRectangleComponent&& other) = delete;

		virtual void Awake() override {};
		virtual void Update([[maybe_unused]] float deltaTime) override {};
		virtual void Render() override {};

		void SetHitboxSize(float newWidth, float newHeight);
		void SetHitboxOffset(float offsetX, float offsetY);

		bool IsOverlapping(const Position2D & point) const;
		bool IsOverlapping(const Circle & hitbox) const;
		bool IsOverlapping(const Rectangle & hitbox) const;

	private:
		Rectangle m_Hitbox;

	};

}