#include "MiniginPCH.h"
#include "HitboxCircleComponent.h"
#include "Object.h"
#include <math.h>

using namespace minigin;

HitboxCircleComponent::HitboxCircleComponent(const std::weak_ptr<Object>& object, const std::string& componentName)
	:HitboxCircleComponent(object, 0.f, 0.f, 0.f, componentName)
{
}

HitboxCircleComponent::HitboxCircleComponent(const std::weak_ptr<Object>& object, float size, const std::string& componentName)
	:HitboxCircleComponent(object, size, 0.f, 0.f, componentName)
{
}

HitboxCircleComponent::HitboxCircleComponent(const std::weak_ptr<Object>& object, float size, float offsetX, float offsetY, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_Hitbox{offsetX, offsetY, size}
{
}

minigin::Circle HitboxCircleComponent::GetHitbox() const
{
	Position2D p = m_pObject.lock()->GetTransform().GetPosition();
	Circle r{ m_Hitbox };
	r.x += p.x;
	r.y += p.y;
	return r;
}

void HitboxCircleComponent::SetHitboxSize(float newSize)
{
	m_Hitbox.size = newSize;
}

void HitboxCircleComponent::SetHitboxOffset(float offsetX, float offsetY)
{
	m_Hitbox.x = offsetX;
	m_Hitbox.y = offsetY;
}

bool HitboxCircleComponent::IsOverlapping(const Position2D& point) const
{
	Circle actualHitbox{ GetHitbox() };
	float distance = static_cast<float>(std::sqrt(std::pow(actualHitbox.x - point.x, 2) + std::pow(actualHitbox.y - point.y, 2)));
	return distance < actualHitbox.size;
}

bool HitboxCircleComponent::IsOverlapping(const Circle& hitbox) const
{
	Circle actualHitbox{ GetHitbox() };
	float distance = static_cast<float>(std::sqrt(std::pow(actualHitbox.x - hitbox.x, 2) + std::pow(actualHitbox.y - hitbox.y, 2)));
	return distance < actualHitbox.size + hitbox.size;
}

bool HitboxCircleComponent::IsOverlapping(const Rectangle& hitbox) const
{
	Circle actualHitbox{ GetHitbox() };
	bool isXInside = (actualHitbox.x + m_Hitbox.size > hitbox.x) && (actualHitbox.x - actualHitbox.size < hitbox.x + hitbox.width);
	bool isYInside = (actualHitbox.y + m_Hitbox.size > hitbox.y) && (actualHitbox.y - actualHitbox.size < hitbox.y + hitbox.height);
	return isXInside && isYInside;
}
