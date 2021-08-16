#pragma once
#include <BaseComponent.h>
#include "TransformStruct.h"
using namespace minigin;

class MoveComponent : public BaseComponent
{
public:
	MoveComponent(const std::shared_ptr<Object>& object, const Position2D& speed);
	virtual ~MoveComponent() = default;
	MoveComponent(const MoveComponent& other) = delete;
	MoveComponent(MoveComponent&& other) = delete;
	MoveComponent& operator=(const MoveComponent& other) = delete;
	MoveComponent& operator=(MoveComponent&& other) = delete;

	virtual void Awake() override {};
	virtual void Update(float deltaTime) override;
	virtual void Render() override {};
private:
	Position2D m_Speed;
};

