#pragma once
#include "BaseComponent.h"
#include "HitboxStruct.h"
#include "TransformStruct.h"
namespace minigin
{

	class HitboxCircleComponent : public BaseComponent
	{
	public:
		HitboxCircleComponent(const std::shared_ptr<Object>& object, const std::string& componentName = "none");
		HitboxCircleComponent(const std::shared_ptr<Object>& object, float size, const std::string& componentName = "none");
		HitboxCircleComponent(const std::shared_ptr<Object>& object, float size, float offsetX, float offsetY, const std::string& componentName = "none");
		virtual ~HitboxCircleComponent() = default;
		HitboxCircleComponent(const HitboxCircleComponent& other) = delete;
		HitboxCircleComponent(HitboxCircleComponent&& other) = delete;
		HitboxCircleComponent& operator=(const HitboxCircleComponent& other) = delete;
		HitboxCircleComponent& operator=(HitboxCircleComponent&& other) = delete;

		virtual void Awake() override {};
		virtual void Update([[maybe_unused]] float deltaTime) override {};
		virtual void Render() override {};

		void SetHitboxSize(float newSize);
		void SetHitboxOffset(float offsetX, float offsetY);

		bool IsOverlapping(const Position2D& point) const;
		bool IsOverlapping(const Circle& hitbox) const;
		bool IsOverlapping(const Rectangle& hitbox) const;

	private:
		Circle m_Hitbox;
	};

}