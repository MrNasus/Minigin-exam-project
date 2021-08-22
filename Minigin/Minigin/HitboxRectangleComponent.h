#pragma once
#include "BaseComponent.h"
#include "HitboxStruct.h"
#include "TransformStruct.h"

namespace minigin
{
	class HitboxRectangleComponent : public BaseComponent
	{
	public:
		HitboxRectangleComponent(const std::weak_ptr<Object>& object, const std::string& componentName = "none");
		HitboxRectangleComponent(const std::weak_ptr<Object>& object, float width, float height, const std::string& componentName = "none");
		HitboxRectangleComponent(const std::weak_ptr<Object>& object, float width, float height, float offsetX, float offsetY, const std::string& componentName = "none");
		virtual ~HitboxRectangleComponent() = default;
		HitboxRectangleComponent(const HitboxRectangleComponent& other) = delete;
		HitboxRectangleComponent(HitboxRectangleComponent&& other) = delete;
		HitboxRectangleComponent& operator=(const HitboxRectangleComponent& other) = delete;
		HitboxRectangleComponent& operator=(HitboxRectangleComponent&& other) = delete;

		virtual void Update([[maybe_unused]] float deltaTime) override {};
		virtual void Render() override {};

		void SetHitboxSize(float newWidth, float newHeight);
		void SetHitboxOffset(float offsetX, float offsetY);
		Rectangle GetHitbox() const;

		bool IsOverlapping(const Position2D & point) const;
		bool IsOverlapping(const Circle & hitbox) const;
		bool IsOverlapping(const Rectangle & hitbox) const;

	private:
		Rectangle m_Hitbox;

	};

}