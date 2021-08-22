#pragma once
#include <BaseComponent.h>
class BulletManagerComponent : public minigin::BaseComponent
{
public:
	BulletManagerComponent(const std::weak_ptr<minigin::Object>& object, const std::string& componentName = "none");
	virtual ~BulletManagerComponent() = default;
	BulletManagerComponent(const BulletManagerComponent& other) = delete;
	BulletManagerComponent(BulletManagerComponent&& other) = delete;
	BulletManagerComponent& operator=(const BulletManagerComponent& other) = delete;
	BulletManagerComponent& operator=(BulletManagerComponent&& other) = delete;

	virtual void Update([[maybe_unused]] float deltaTime) override {};
	virtual void Render() override {};
private:
};

