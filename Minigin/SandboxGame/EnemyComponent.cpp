#include "EnemyComponent.h"
#include "Object.h"
#include "Renderer.h"

using namespace minigin;

EnemyComponent::EnemyComponent(const std::weak_ptr<minigin::Object>& object, const std::shared_ptr<BulletManagerComponent>& pBulletManager, EnemyType type, float explosionTime, bool isControlled, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_Type{type}
	,m_Border{50.f}
	,m_Health{0}
	,m_pHitbox{}
	,m_IsControlled{ isControlled }
	,m_pAlive{}
	,m_pExploding{}
	,m_pHealthy{}
	,m_State{EnemyState::Dead}
	,m_WindowHeight{}
	,m_ExplosionTime{explosionTime}
	,m_ExplosionTimer{0.f}
	,m_DiveSpeed{250.f}
	,m_pBulletManager{pBulletManager}
{
	int w, h;
	Renderer::GetInstance().GetWindowSize(w, h);
	m_WindowHeight = float(h);

	std::shared_ptr<Object> pO = m_pObject.lock();
	m_pAlive = pO->GetComponent<SpriteComponent>("AliveVisual");
	m_pHealthy = pO->GetComponent<SpriteComponent>("HealthyVisual");
	m_pExploding = pO->GetComponent<SpriteComponent>("ExplodingVisual");
	m_pHitbox = pO->GetComponent<HitboxCircleComponent>();

	SetState(EnemyState::Dead);
}

void EnemyComponent::Update(float deltaTime)
{
	Transform t{};
	switch (m_State)
	{
	case EnemyState::Idle:
		break;
	case EnemyState::Diving:
		t = m_pObject.lock()->GetTransform();
		t.SetPosition({ t.GetPosition().x, t.GetPosition().y + (m_DiveSpeed * deltaTime) });
		if (m_IsDiveLoopDone) 
		{
			if (t.GetPosition().y >= m_OriginalPosition.y)
			{
				SetState(EnemyState::Idle);
			}
		}
		else
		{
			if (t.GetPosition().y >= m_WindowHeight + m_Border)
			{
				t.SetPosition({ t.GetPosition().x , -m_Border });
				m_IsDiveLoopDone = true;
			}
		}
		m_pObject.lock()->SetTransform(t);
		break;
	case EnemyState::Beaming:
		break;
	case EnemyState::Exploding:
		m_ExplosionTimer += deltaTime;
		if (m_ExplosionTimer >= m_ExplosionTime)
		{
			SetState(EnemyState::Dead);
		}
		break;
	case EnemyState::Dead:
		break;
	default:
		break;
	}

	if (!IsDead())
	{
		if (m_pBulletManager->HitFriendlyBullets(m_pHitbox->GetHitbox()))
		{
			GetHit();
		}
	}
}

void EnemyComponent::SetState(EnemyState state, bool shoot)
{
	if (shoot)
	{
		m_pBulletManager->CreateBullet({ float((rand() % 100) - 50), 350.f }, { m_pHitbox->GetHitbox().x, m_pHitbox->GetHitbox().y }, false);
	}
	m_State = state;
	Transform t{};
	switch (m_State)
	{
	case EnemyState::Idle:
		break;
	case EnemyState::Diving:
		m_IsDiveLoopDone = false;
		break;
	case EnemyState::Beaming:
		break;
	case EnemyState::Exploding:
		m_pExploding->ResetClock();
		m_ExplosionTimer = 0.f;
		m_pExploding->SetVisible(true);
		m_pAlive->SetVisible(false);
		if (m_pHealthy != nullptr)
		{
			m_pHealthy->SetVisible(false);
		}
		break;
	case EnemyState::Dead:
		m_pExploding->SetVisible(false);
		m_pAlive->SetVisible(false);
		if (m_pHealthy != nullptr)
		{
			m_pHealthy->SetVisible(false);
		}
		t.SetPosition({ -100.f, 0.f });
		m_pObject.lock()->SetTransform(t);
		break;
	default:
		break;
	}
}

const EnemyState& EnemyComponent::GetState() const
{
	return m_State;
}

void EnemyComponent::GetHit()
{
	--m_Health;
	if (m_Health == 1)
	{
		if (m_pHealthy != nullptr)
		{
			m_pHealthy->SetVisible(false);
		}
		m_pAlive->SetVisible(true);
	}
	else if (m_Health == 0)
	{
		SetState(EnemyState::Exploding);
	}
	else
	{
		SetState(EnemyState::Dead);
	}
}

const std::shared_ptr<minigin::HitboxCircleComponent>& EnemyComponent::GetHitbox() const
{
	return m_pHitbox;
}

void EnemyComponent::Revive(const minigin::Position2D& position)
{
	m_State = EnemyState::Idle;
	Transform t{};
	t.SetPosition(position);
	m_OriginalPosition = position;
	m_pObject.lock()->SetTransform(t);
	switch (m_Type)
	{
	case EnemyComponent::EnemyType::Goei:
	case EnemyComponent::EnemyType::Zako:
		m_Health = 1;
		m_pAlive->SetVisible(true);
		break;
	case EnemyComponent::EnemyType::Boss:
	case EnemyComponent::EnemyType::Controlled:
		m_Health = 2;
		m_pHealthy->SetVisible(true);
		break;
	}
}

bool EnemyComponent::IsDead() const
{
	return m_State == EnemyState::Dead || m_State == EnemyState::Exploding;
}

bool EnemyComponent::IsInUse() const
{
	return m_State != EnemyState::Dead;
}
