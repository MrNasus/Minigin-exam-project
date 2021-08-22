#include "MiniginPCH.h"
#include "HitboxCircleComponent.h"
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

void minigin::HitboxCircleComponent::SetHitboxSize(float newSize)
{
	m_Hitbox.size = newSize;
}

void minigin::HitboxCircleComponent::SetHitboxOffset(float offsetX, float offsetY)
{
	m_Hitbox.x = offsetX;
	m_Hitbox.y = offsetY;
}

bool minigin::HitboxCircleComponent::IsOverlapping(const Position2D& point) const
{
	float distance = static_cast<float>(std::sqrt(std::pow(m_Hitbox.x - point.x, 2) + std::pow(m_Hitbox.y - point.y, 2)));
	return distance < m_Hitbox.size;
}

bool minigin::HitboxCircleComponent::IsOverlapping(const Circle& hitbox) const
{
	float distance = static_cast<float>(std::sqrt(std::pow(m_Hitbox.x - hitbox.x, 2) + std::pow(m_Hitbox.y - hitbox.y, 2)));
	return distance < m_Hitbox.size + hitbox.size;
}

bool minigin::HitboxCircleComponent::IsOverlapping(const Rectangle& hitbox) const
{
	bool isXInside = (m_Hitbox.x + m_Hitbox.size > hitbox.x) && (m_Hitbox.x - m_Hitbox.size < hitbox.x + hitbox.width);
	bool isYInside = (m_Hitbox.y + m_Hitbox.size > hitbox.y) && (m_Hitbox.y - m_Hitbox.size < hitbox.y + hitbox.height);
	return isXInside && isYInside;
}
