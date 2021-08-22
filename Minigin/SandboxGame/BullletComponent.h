#pragma once
#include <BaseComponent.h>
#include "TransformStruct.h"
class BullletComponent : public minigin::BaseComponent
{
public:
	BullletComponent(const std::weak_ptr<minigin::Object>& object, const minigin::Position2D& velocity, const std::string& componentName = "none");
	virtual ~BullletComponent() = default;
	BullletComponent(const BullletComponent& other) = delete;
	BullletComponent(BullletComponent&& other) = delete;
	BullletComponent& operator=(const BullletComponent& other) = delete;
	BullletComponent& operator=(BullletComponent&& other) = delete;

	virtual void Update(float deltaTime) override;
	virtual void Render() override {};

	void Recycle(const minigin::Position2D& velocity, const minigin::Position2D& position);
	void Deactivate();
private:
	minigin::Position2D m_Velocity;
	bool m_IsInUse;
};

