#include "EnemyManagerComponent.h"
#include "BulletManagerComponent.h"
#include "Object.h"
#include "Scene.h"
#include "SceneSwapComponent.h"

using namespace minigin;

EnemyManagerComponent::EnemyManagerComponent(const std::weak_ptr<minigin::Object>& object, const std::shared_ptr<BulletManagerComponent>& bulletManager, unsigned int maxEnemyPoolSize, bool playerController, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_MaxEnemyPoolSize{maxEnemyPoolSize}
	,m_AccuAttackSec{0.f}
	,m_AttackCD{1.f}
	,m_pBossEnemies{}
	,m_pGoeiEnemies{}
	,m_pZakoEnemeies{}
	,m_PlayerController{playerController}
	,m_WaveNumber{0}
{
	size_t maxBossPoolSize{ m_MaxEnemyPoolSize };
	if (m_PlayerController)
	{
		maxBossPoolSize = 1;
	}

	m_pBossEnemies.reserve(maxBossPoolSize);
	m_pGoeiEnemies.reserve(m_MaxEnemyPoolSize);
	m_pZakoEnemeies.reserve(m_MaxEnemyPoolSize);


	std::shared_ptr<Scene> game = nullptr;
	if (!SceneManager::GetInstance().GetScene("Game", game))
	{
		return;
	}

	//add bosses
	for (size_t i = 0; i < maxBossPoolSize; ++i)
	{
		std::shared_ptr<Object> boss = std::make_shared<Object>();
		boss->AddComponent(std::make_shared<SpriteComponent>(boss, "BossGreen.png", 2, 0.4f, "HealthyVisual"));
		boss->AddComponent(std::make_shared<SpriteComponent>(boss, "BossBlue.png", 2, 0.4f, "AliveVisual"));
		boss->AddComponent(std::make_shared<SpriteComponent>(boss, "GalagaExplosion.png", 5, 0.25f, "ExplodingVisual"));
		boss->AddComponent(std::make_shared<HitboxCircleComponent>(boss, 16.f));
		std::shared_ptr<EnemyComponent> bossComp = std::make_shared<EnemyComponent>(boss, bulletManager, EnemyComponent::EnemyType::Boss, 0.25f, playerController);
		boss->AddComponent(bossComp);
		m_pBossEnemies.push_back(bossComp);
		game->Add(boss);
	}

	//add goei
	for (size_t i = 0; i < m_MaxEnemyPoolSize; ++i)
	{
		std::shared_ptr<Object> goei = std::make_shared<Object>();
		goei->AddComponent(std::make_shared<SpriteComponent>(goei, "Goei.png", 2, 0.4f, "AliveVisual"));
		goei->AddComponent(std::make_shared<SpriteComponent>(goei, "GalagaExplosion.png", 5, 0.25f, "ExplodingVisual"));
		goei->AddComponent(std::make_shared<HitboxCircleComponent>(goei, 12.f));
		std::shared_ptr<EnemyComponent> goeiComp = std::make_shared<EnemyComponent>(goei, bulletManager, EnemyComponent::EnemyType::Goei, 0.25f, false);
		goei->AddComponent(goeiComp);
		m_pGoeiEnemies.push_back(goeiComp);
		game->Add(goei);
	}

	//add zako
	for (size_t i = 0; i < m_MaxEnemyPoolSize; ++i)
	{
		std::shared_ptr<Object> zako = std::make_shared<Object>();
		zako->AddComponent(std::make_shared<SpriteComponent>(zako, "Zako.png", 2, 0.4f, "AliveVisual"));
		zako->AddComponent(std::make_shared<SpriteComponent>(zako, "GalagaExplosion.png", 5, 0.25f, "ExplodingVisual"));
		zako->AddComponent(std::make_shared<HitboxCircleComponent>(zako, 12.f));
		std::shared_ptr<EnemyComponent> zakoComp = std::make_shared<EnemyComponent>(zako, bulletManager, EnemyComponent::EnemyType::Zako, 0.25f, false);
		zako->AddComponent(zakoComp);
		m_pZakoEnemeies.push_back(zakoComp);
		game->Add(zako);
	}

	SpawnNextWave();
}

void EnemyManagerComponent::Update(float deltaTime)
{
	m_AccuAttackSec += deltaTime;
	if (m_AccuAttackSec >= m_AttackCD)
	{
		m_AccuAttackSec = 0.f;
		int type = rand() % 3;
		if (type == 0)
		{
			if (m_pBossEnemies[0]->GetState() == EnemyState::Idle)
			{
				m_pBossEnemies[0]->SetState(EnemyState::Diving, rand()%2);
			}
		}
		else if (type == 1)
		{
			int nr = rand() % 3;
			if (m_pGoeiEnemies[nr]->GetState() == EnemyState::Idle)
			{
				m_pGoeiEnemies[nr]->SetState(EnemyState::Diving, rand() % 2);
			}
		}
		else if (type == 2)
		{
			int nr = rand() % 5;
			if (m_pZakoEnemeies[nr]->GetState() == EnemyState::Idle)
			{
				m_pZakoEnemeies[nr]->SetState(EnemyState::Diving, rand() % 2);
			}
		}
	}

	bool enemyAlive = false;
	for (const auto& enemy : m_pBossEnemies)
	{
		if (enemy->IsInUse())
		{
			enemyAlive = true;
			break;
		}
	}
	if (!enemyAlive)
	{
		for (const auto& enemy : m_pGoeiEnemies)
		{
			if (enemy->IsInUse())
			{
				enemyAlive = true;
				break;
			}
		}
	}
	if (!enemyAlive)
	{
		for (const auto& enemy : m_pZakoEnemeies)
		{
			if (enemy->IsInUse())
			{
				enemyAlive = true;
				break;
			}
		}
	}

	if (enemyAlive == false)
	{
		SpawnNextWave();
	}
}

bool EnemyManagerComponent::HitEnemies(const minigin::Circle& hitbox)
{
	for (auto& enemy : m_pBossEnemies)
	{
		if (enemy->GetHitbox()->IsOverlapping(hitbox))
		{
			return true;
		}
	}
	for (auto& enemy : m_pGoeiEnemies)
	{
		if (enemy->GetHitbox()->IsOverlapping(hitbox))
		{
			return true;
		}
	}
	for (auto& enemy : m_pZakoEnemeies)
	{
		if (enemy->GetHitbox()->IsOverlapping(hitbox))
		{
			return true;
		}
	}
	return false;
}

void EnemyManagerComponent::ResetWave()
{
	m_WaveNumber = 0;
}

void EnemyManagerComponent::SpawnNextWave()
{
	if (m_WaveNumber == 0)
	{
		m_pBossEnemies[0]->Revive({ 320.f, 40.f });
		m_pGoeiEnemies[0]->Revive({ 280.f, 80.f });
		m_pGoeiEnemies[1]->Revive({ 320.f, 80.f });
		m_pGoeiEnemies[2]->Revive({ 360.f, 80.f });
		m_pZakoEnemeies[0]->Revive({ 240.f, 120.f });
		m_pZakoEnemeies[1]->Revive({ 280.f, 120.f });
		m_pZakoEnemeies[2]->Revive({ 320.f, 120.f });
		m_pZakoEnemeies[3]->Revive({ 360.f, 120.f });
		m_pZakoEnemeies[4]->Revive({ 400.f, 120.f });
	}
	if (m_WaveNumber == 1)
	{
		m_pBossEnemies[0]->Revive({ 320.f, 40.f });
		m_pGoeiEnemies[0]->Revive({ 280.f, 80.f });
		m_pGoeiEnemies[1]->Revive({ 320.f, 80.f });
		m_pGoeiEnemies[2]->Revive({ 360.f, 80.f });
		m_pZakoEnemeies[0]->Revive({ 240.f, 120.f });
		m_pZakoEnemeies[1]->Revive({ 280.f, 120.f });
		m_pZakoEnemeies[2]->Revive({ 320.f, 120.f });
		m_pZakoEnemeies[3]->Revive({ 360.f, 120.f });
		m_pZakoEnemeies[4]->Revive({ 400.f, 120.f });
	}
	if (m_WaveNumber == 2)
	{
		m_pBossEnemies[0]->Revive({ 320.f, 40.f });
		m_pGoeiEnemies[0]->Revive({ 280.f, 80.f });
		m_pGoeiEnemies[1]->Revive({ 320.f, 80.f });
		m_pGoeiEnemies[2]->Revive({ 360.f, 80.f });
		m_pZakoEnemeies[0]->Revive({ 240.f, 120.f });
		m_pZakoEnemeies[1]->Revive({ 280.f, 120.f });
		m_pZakoEnemeies[2]->Revive({ 320.f, 120.f });
		m_pZakoEnemeies[3]->Revive({ 360.f, 120.f });
		m_pZakoEnemeies[4]->Revive({ 400.f, 120.f });
	}
	if (m_WaveNumber == 3)
	{
		ResetWave();
		m_pObject.lock()->GetComponent<SceneSwapComponent>()->Swap();
	}
	++m_WaveNumber;
}
