#pragma once
#include <BaseComponent.h>
#include "HitboxCircleComponent.h"
#include "TransformStruct.h"
#include "SpriteComponent.h"
#include "TransformStruct.h"
#include "BulletManagerComponent.h"
#include "EnemyState.h"

class EnemyComponent : public minigin::BaseComponent
{
public:
	enum class EnemyType
	{
		Goei,
		Zako,
		Boss,
		Controlled
	};

	EnemyComponent(const std::weak_ptr<minigin::Object>& object, const std::shared_ptr<BulletManagerComponent>& pBulletManager, EnemyType type, float explosionTime, bool isControlled = false, const std::string& componentName = "none");
	virtual ~EnemyComponent() = default;
	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;

	virtual void Update(float deltaTime) override;
	virtual void Render() override {};

	void SetState(EnemyState state, bool shoot = false);
	void GetHit();

	const std::shared_ptr<minigin::HitboxCircleComponent>& GetHitbox() const;
	void Revive(const minigin::Position2D & position);
	bool IsDead() const;
	bool IsInUse() const;
private:
	std::shared_ptr<minigin::HitboxCircleComponent> m_pHitbox;
	std::shared_ptr<minigin::SpriteComponent> m_pAlive;
	std::shared_ptr<minigin::SpriteComponent> m_pHealthy;
	std::shared_ptr<minigin::SpriteComponent> m_pExploding;
	std::shared_ptr<BulletManagerComponent> m_pBulletManager;
	minigin::Position2D m_Velocity;
	bool m_IsControlled;
	EnemyState m_State;
	EnemyType m_Type;
	int m_Health;
	minigin::Position2D m_OriginalPosition;
	float m_WindowHeight;
	float m_Border;
	float m_ExplosionTime;
	float m_ExplosionTimer;
	float m_DiveSpeed;
	bool m_IsDiveLoopDone;
};

