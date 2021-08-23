#pragma once
#include <BaseComponent.h>
#include <vector>
#include "EnemyComponent.h"

class BulletManagerComponent;
class EnemyManagerComponent : public minigin::BaseComponent
{
public:
	EnemyManagerComponent(const std::weak_ptr<minigin::Object>& object, const std::shared_ptr<BulletManagerComponent>& bulletManager, unsigned int maxEnemyPoolSize, bool isPlayerController, const std::string& componentName = "none");
	virtual ~EnemyManagerComponent() = default;
	EnemyManagerComponent(const EnemyManagerComponent& other) = delete;
	EnemyManagerComponent(EnemyManagerComponent&& other) = delete;
	EnemyManagerComponent& operator=(const EnemyManagerComponent& other) = delete;
	EnemyManagerComponent& operator=(EnemyManagerComponent&& other) = delete;

	virtual void Update(float deltaTime) override;
	virtual void Render() override {};

	bool HitEnemies(const minigin::Circle & hitbox);
	void ResetWave();
	void SpawnNextWave();

private:

	std::vector<std::shared_ptr<EnemyComponent>> m_pBossEnemies;
	std::vector<std::shared_ptr<EnemyComponent>> m_pGoeiEnemies;
	std::vector<std::shared_ptr<EnemyComponent>> m_pZakoEnemeies;

	unsigned int m_WaveNumber;
	unsigned int m_MaxEnemyPoolSize;
	float m_AccuAttackSec;
	float m_AttackCD;
	bool m_PlayerController;
};

