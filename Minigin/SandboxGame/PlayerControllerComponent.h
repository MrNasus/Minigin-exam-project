#pragma once
#include <BaseComponent.h>
#include "HitboxCircleComponent.h"

class PlayerControllerComponent : public minigin::BaseComponent
{
public:
	PlayerControllerComponent(const std::weak_ptr<minigin::Object>& object, bool isSingleplayer, bool isFirstPlayer = true, const std::string& componentName = "none");
	virtual ~PlayerControllerComponent() = default;
	PlayerControllerComponent(const PlayerControllerComponent& other) = delete;
	PlayerControllerComponent(PlayerControllerComponent&& other) = delete;
	PlayerControllerComponent& operator=(const PlayerControllerComponent& other) = delete;
	PlayerControllerComponent& operator=(PlayerControllerComponent&& other) = delete;

	virtual void Update( float deltaTime) override;
	virtual void Render() override {};

private:
	int m_MoveLeftId;
	int m_MoveRightId;
	int m_ShootId;
	int m_Lives;
	float m_FlySpeed;
	float m_LeftWindowLimit;
	float m_RightWindowLimit;
	float m_ShootCD;
	float m_AccuShotTime;

	std::shared_ptr<minigin::HitboxCircleComponent> m_pHitbox;
};

