#pragma once
#include <BaseComponent.h>
#include "HitboxRectangleComponent.h"
#include "TransformStruct.h"

class BulletComponent : public minigin::BaseComponent
{
public:
	BulletComponent(const std::weak_ptr<minigin::Object>& object, const minigin::Position2D& velocity, const std::string& componentName = "none");
	virtual ~BulletComponent() = default;
	BulletComponent(const BulletComponent& other) = delete;
	BulletComponent(BulletComponent&& other) = delete;
	BulletComponent& operator=(const BulletComponent& other) = delete;
	BulletComponent& operator=(BulletComponent&& other) = delete;

	virtual void Update(float deltaTime) override;
	virtual void Render() override {};

	const std::shared_ptr<minigin::HitboxRectangleComponent>& GetHitbox() const;
	void Recycle(const minigin::Position2D& velocity, const minigin::Position2D& position);
	void Deactivate();
	bool IsInUse() const;
private:
	std::shared_ptr<minigin::HitboxRectangleComponent> m_Hitbox;
	minigin::Position2D m_Velocity;
	bool m_IsInUse;
};

