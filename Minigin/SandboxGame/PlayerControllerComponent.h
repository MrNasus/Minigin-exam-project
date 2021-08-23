#pragma once
#include <BaseComponent.h>
#include "HitboxCircleComponent.h"
#include "BulletManagerComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"

class EnemyManagerComponent;
class PlayerControllerComponent : public minigin::BaseComponent
{
public:
	PlayerControllerComponent(const std::weak_ptr<minigin::Object>& object, const std::shared_ptr<BulletManagerComponent>& pBulletManager, const std::shared_ptr<EnemyManagerComponent>& pEnemyManager, bool isSingleplayer, bool isFirstPlayer = true, const std::string& componentName = "none");
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
	float m_BulletSpeed;
	float m_AccuExplodeSec;
	float m_ExplodeTime;
	bool m_JustExploded;

	std::shared_ptr<minigin::HitboxCircleComponent> m_pHitbox;
	std::shared_ptr<minigin::TextureComponent> m_pTexture;
	std::shared_ptr<minigin::SpriteComponent> m_pExplosion;
	std::shared_ptr<BulletManagerComponent> m_pBulletManager;
	std::shared_ptr<EnemyManagerComponent> m_pEnemyManager;
};

