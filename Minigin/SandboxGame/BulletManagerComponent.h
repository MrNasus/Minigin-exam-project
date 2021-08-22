#pragma once
#include <BaseComponent.h>
#include "BulletComponent.h"
#include "TransformStruct.h"
#include "HitboxRectangleComponent.h"
#include "HitboxStruct.h"
#include <vector>
#include <memory>

class BulletManagerComponent : public minigin::BaseComponent
{
public:
	BulletManagerComponent(const std::weak_ptr<minigin::Object>& object, unsigned int maxBulletPoolSize, const std::shared_ptr<minigin::HitboxRectangleComponent>& windowBorder, const std::string& componentName = "none");
	virtual ~BulletManagerComponent() = default;
	BulletManagerComponent(const BulletManagerComponent& other) = delete;
	BulletManagerComponent(BulletManagerComponent&& other) = delete;
	BulletManagerComponent& operator=(const BulletManagerComponent& other) = delete;
	BulletManagerComponent& operator=(BulletManagerComponent&& other) = delete;

	virtual void Update([[maybe_unused]] float deltaTime) override;
	virtual void Render() override {};

	bool HitFriendlyBullets(const minigin::Circle& hitbox);
	bool HitEnemyBullets(const minigin::Circle& hitbox);

	void CreateBullet(const minigin::Position2D& velocity, const minigin::Position2D& position, bool isFriendly);
private:
	unsigned int m_MaxBulletPoolSize;
	std::vector<std::shared_ptr<BulletComponent>> m_FriendlyBullets;
	std::vector<std::shared_ptr<BulletComponent>> m_EnemeyBullets;
	std::shared_ptr<minigin::HitboxRectangleComponent> m_WindowBorder;
};

