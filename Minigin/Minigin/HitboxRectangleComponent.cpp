#include "MiniginPCH.h"
#include "HitboxRectangleComponent.h"

using namespace minigin;

HitboxRectangleComponent::HitboxRectangleComponent(const std::shared_ptr<Object>& object)
	:HitboxRectangleComponent(object, 0.f, 0.f, 0.f, 0.f)
{
}

HitboxRectangleComponent::HitboxRectangleComponent(const std::shared_ptr<Object>& object, float width, float height)
	: HitboxRectangleComponent(object, width, height, 0.f, 0.f)
{
}

HitboxRectangleComponent::HitboxRectangleComponent(const std::shared_ptr<Object>& object, float width, float height, float offsetX, float offsetY)
	:BaseComponent(object)
	,m_Hitbox{offsetX, offsetY, width, height}
{
}

void minigin::HitboxRectangleComponent::SetHitboxSize(float newWidth, float newHeight)
{
	m_Hitbox.width = newWidth;
	m_Hitbox.height = newHeight;
}

void minigin::HitboxRectangleComponent::SetHitboxOffset(float offsetX, float offsetY)
{
	m_Hitbox.x = offsetX;
	m_Hitbox.y = offsetY;
}

bool minigin::HitboxRectangleComponent::IsOverlapping(const Position2D& point) const
{
	bool isXInside = m_Hitbox.x < point.x && m_Hitbox.x + m_Hitbox.width > point.x;
	bool isYInside = m_Hitbox.y < point.y && m_Hitbox.y + m_Hitbox.height > point.y;
	return isXInside && isYInside;
}

bool minigin::HitboxRectangleComponent::IsOverlapping(const Circle& hitbox) const
{
	bool isXInside = (m_Hitbox.x < hitbox.x + hitbox.size) && (m_Hitbox.x + m_Hitbox.width > hitbox.x - hitbox.size);
	bool isYInside = (m_Hitbox.y < hitbox.y + hitbox.size) && (m_Hitbox.y + m_Hitbox.height > hitbox.y - hitbox.size);
	return isXInside && isYInside;
}

bool minigin::HitboxRectangleComponent::IsOverlapping(const Rectangle& hitbox) const
{
	bool isXInside = (m_Hitbox.x < hitbox.x + hitbox.width) && (m_Hitbox.x + m_Hitbox.width > hitbox.x);
	bool isYInside = (m_Hitbox.y < hitbox.y + hitbox.height) && (m_Hitbox.y + m_Hitbox.height > hitbox.y);
	return isXInside && isYInside;
}
