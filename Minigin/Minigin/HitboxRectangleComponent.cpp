#include "MiniginPCH.h"
#include "HitboxRectangleComponent.h"
#include "Object.h"

using namespace minigin;

HitboxRectangleComponent::HitboxRectangleComponent(const std::weak_ptr<Object>& object, const std::string& componentName)
	:HitboxRectangleComponent(object, 0.f, 0.f, 0.f, 0.f, componentName)
{
}

HitboxRectangleComponent::HitboxRectangleComponent(const std::weak_ptr<Object>& object, float width, float height, const std::string& componentName)
	: HitboxRectangleComponent(object, width, height, 0.f, 0.f, componentName)
{
}

HitboxRectangleComponent::HitboxRectangleComponent(const std::weak_ptr<Object>& object, float width, float height, float offsetX, float offsetY, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_Hitbox{offsetX, offsetY, width, height}
{
	m_Hitbox.x -= width / 2.f;
	m_Hitbox.y -= height / 2.f;
}

void HitboxRectangleComponent::SetHitboxSize(float newWidth, float newHeight)
{
	m_Hitbox.width = newWidth;
	m_Hitbox.height = newHeight;
}

void HitboxRectangleComponent::SetHitboxOffset(float offsetX, float offsetY)
{
	m_Hitbox.x = offsetX;
	m_Hitbox.y = offsetY;
}

minigin::Rectangle HitboxRectangleComponent::GetHitbox() const
{
	Position2D p = m_pObject.lock()->GetTransform().GetPosition();
	Rectangle r{ m_Hitbox };
	r.x += p.x;
	r.y += p.y;
	return r;
}

bool HitboxRectangleComponent::IsOverlapping(const Position2D& point) const
{
	Rectangle actualHitbox{ GetHitbox() };
	bool isXInside = actualHitbox.x < point.x && actualHitbox.x + actualHitbox.width > point.x;
	bool isYInside = actualHitbox.y < point.y && actualHitbox.y + actualHitbox.height > point.y;
	return isXInside && isYInside;
}

bool HitboxRectangleComponent::IsOverlapping(const Circle& hitbox) const
{
	Rectangle actualHitbox{ GetHitbox() };
	bool isXInside = (actualHitbox.x < hitbox.x + hitbox.size) && (actualHitbox.x + actualHitbox.width > hitbox.x - hitbox.size);
	bool isYInside = (actualHitbox.y < hitbox.y + hitbox.size) && (actualHitbox.y + actualHitbox.height > hitbox.y - hitbox.size);
	return isXInside && isYInside;
}

bool HitboxRectangleComponent::IsOverlapping(const Rectangle& hitbox) const
{
	Rectangle actualHitbox{ GetHitbox() };
	bool isXInside = (actualHitbox.x < hitbox.x + hitbox.width) && (actualHitbox.x + actualHitbox.width > hitbox.x);
	bool isYInside = (actualHitbox.y < hitbox.y + hitbox.height) && (actualHitbox.y + actualHitbox.height > hitbox.y);
	return isXInside && isYInside;
}
