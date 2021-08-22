#pragma once
#include <BaseComponent.h>
#include "TransformStruct.h"

class MoveComponent : public minigin::BaseComponent
{
public:
	MoveComponent(const std::weak_ptr<minigin::Object>& object, const minigin::Position2D& speed, const std::string& componentName = "none");
	virtual ~MoveComponent() = default;
	MoveComponent(const MoveComponent& other) = delete;
	MoveComponent(MoveComponent&& other) = delete;
	MoveComponent& operator=(const MoveComponent& other) = delete;
	MoveComponent& operator=(MoveComponent&& other) = delete;

	virtual void Update(float deltaTime) override;
	virtual void Render() override {};
private:
	minigin::Position2D m_Speed;
};

