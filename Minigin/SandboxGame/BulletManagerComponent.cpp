#include "BulletManagerComponent.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Scene.h"
#include "Object.h"
#include "HitboxRectangleComponent.h"
#include "TextureComponent.h"

using namespace minigin;

BulletManagerComponent::BulletManagerComponent(const std::weak_ptr<minigin::Object>& object, unsigned int maxBulletPoolSize, const std::shared_ptr<minigin::HitboxRectangleComponent>& windowBorder, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_MaxBulletPoolSize{maxBulletPoolSize}
	,m_EnemeyBullets{}
	,m_FriendlyBullets{}
	,m_WindowBorder{windowBorder}
{
	m_FriendlyBullets.reserve(m_MaxBulletPoolSize);
	m_EnemeyBullets.reserve(m_MaxBulletPoolSize);
	Transform t{};
	t.SetPosition(Position2D{-100.f, -100.f});

	std::shared_ptr<Scene> game = nullptr;
	if (!SceneManager::GetInstance().GetScene("Game", game))
	{
		return;
	}
	for (size_t i = 0; i < m_MaxBulletPoolSize; ++i)
	{
		std::shared_ptr<Object> bullet = std::make_shared<Object>();
		bullet->AddComponent(std::make_shared<HitboxRectangleComponent>(bullet, 6.f, 16.f));
		bullet->AddComponent(std::make_shared<TextureComponent>(bullet, "StarfighterProjectile.png"));
		std::shared_ptr<BulletComponent> bulletComp = std::make_shared<BulletComponent>(bullet, Position2D{});
		bullet->AddComponent(bulletComp);
		m_FriendlyBullets.push_back(bulletComp);
		bullet->SetTransform(t);
		game->Add(bullet);
	}
	for (size_t i = 0; i < m_MaxBulletPoolSize; ++i)
	{
		std::shared_ptr<Object> bullet = std::make_shared<Object>();
		bullet->AddComponent(std::make_shared<HitboxRectangleComponent>(bullet, 6.f, 16.f));
		bullet->AddComponent(std::make_shared<TextureComponent>(bullet, "GalagaProjectile.png"));
		std::shared_ptr<BulletComponent> bulletComp = std::make_shared<BulletComponent>(bullet, Position2D{});
		bullet->AddComponent(bulletComp);
		m_EnemeyBullets.push_back(bulletComp);
		bullet->SetTransform(t);
		game->Add(bullet);
	}
}

void BulletManagerComponent::Update([[maybe_unused]] float deltaTime)
{
	for (auto& bullet : m_FriendlyBullets)
	{
		if (bullet->IsInUse())
		{
			if (!m_WindowBorder->IsOverlapping(bullet->GetHitbox()->GetHitbox()))
			{
				bullet->Deactivate();
			}
		}
	}
	for (auto& bullet : m_EnemeyBullets)
	{
		if (bullet->IsInUse())
		{
			if (!m_WindowBorder->IsOverlapping(bullet->GetHitbox()->GetHitbox()))
			{
				bullet->Deactivate();
			}
		}
	}
}

bool BulletManagerComponent::HitFriendlyBullets(const Circle& hitbox)
{
	bool hitAtLeastOne = false;
	for (auto& bullet : m_FriendlyBullets)
	{
		if (bullet->GetHitbox()->IsOverlapping(hitbox))
		{
			hitAtLeastOne = true;
			bullet->Deactivate();
		}
	}
	return hitAtLeastOne;
}

bool BulletManagerComponent::HitEnemyBullets(const Circle& hitbox)
{
	bool hitAtLeastOne = false;
	for (auto& bullet : m_EnemeyBullets)
	{
		if (bullet->GetHitbox()->IsOverlapping(hitbox))
		{
			hitAtLeastOne = true;
			bullet->Deactivate();
		}
	}
	return hitAtLeastOne;
}

void BulletManagerComponent::CreateBullet(const minigin::Position2D& velocity, const minigin::Position2D& position, bool isFriendly)
{
	if (isFriendly)
	{
		for (size_t i = 0; i < m_FriendlyBullets.size(); ++i)
		{
			if (!m_FriendlyBullets[i]->IsInUse())
			{
				m_FriendlyBullets[i]->Recycle(velocity, position);
				return;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < m_EnemeyBullets.size(); ++i)
		{
			if (!m_EnemeyBullets[i]->IsInUse())
			{
				m_EnemeyBullets[i]->Recycle(velocity, position);
				return;
			}
		}
	}
}
