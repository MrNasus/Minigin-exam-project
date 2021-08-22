#include "PlayerControllerComponent.h"
#include "InputManager.h"
#include "Object.h"
#include "Transform.h"
#include <iostream>

using namespace minigin;

PlayerControllerComponent::PlayerControllerComponent(const std::weak_ptr<minigin::Object>& object, bool isSingleplayer, bool isFirstPlayer, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_MoveLeftId{}
	,m_MoveRightId{}
	,m_ShootId{}
	,m_LeftWindowLimit{30.f}
	,m_RightWindowLimit{610.f}
	,m_FlySpeed{400.f}
	,m_ShootCD{0.4f}
	,m_AccuShotTime{0.f}
{
	m_pHitbox = m_pObject.lock()->GetComponent<HitboxCircleComponent>();
	if (isSingleplayer)
	{
		InputBinding bindingLeft{ 3, InputTriggerState::Down, ControllerButton::DpadLeft, KeyboardButton::Left };
		InputManager::GetInstance().AddInputBinding(bindingLeft);
		InputBinding bindingRight{ 4, InputTriggerState::Down, ControllerButton::DpadRight, KeyboardButton::Right };
		InputManager::GetInstance().AddInputBinding(bindingRight);
		InputBinding bindingShoot{ 5, InputTriggerState::Down, ControllerButton::ButtonA, KeyboardButton::Space };
		InputManager::GetInstance().AddInputBinding(bindingShoot);
		m_MoveLeftId = 3;
		m_MoveRightId = 4;
		m_ShootId = 5;
	}
	else
	{
		if (isFirstPlayer)
		{
			InputBinding bindingLeft{ 3, InputTriggerState::Down, ControllerButton::None, KeyboardButton::Left };
			InputManager::GetInstance().AddInputBinding(bindingLeft);
			InputBinding bindingRight{ 4, InputTriggerState::Down, ControllerButton::None, KeyboardButton::Right };
			InputManager::GetInstance().AddInputBinding(bindingRight);
			InputBinding bindingShoot{ 5, InputTriggerState::Down, ControllerButton::None, KeyboardButton::Space };
			InputManager::GetInstance().AddInputBinding(bindingShoot);
			m_MoveLeftId = 3;
			m_MoveRightId = 4;
			m_ShootId = 5;
		}
		else
		{
			InputBinding bindingLeft{ 6, InputTriggerState::Down, ControllerButton::DpadLeft, KeyboardButton::None };
			InputManager::GetInstance().AddInputBinding(bindingLeft);
			InputBinding bindingRight{ 7, InputTriggerState::Down, ControllerButton::DpadRight, KeyboardButton::None };
			InputManager::GetInstance().AddInputBinding(bindingRight);
			InputBinding bindingShoot{ 8, InputTriggerState::Down, ControllerButton::ButtonA, KeyboardButton::None };
			InputManager::GetInstance().AddInputBinding(bindingShoot);
			m_MoveLeftId = 6;
			m_MoveRightId = 7;
			m_ShootId = 8;
		}
	}
}

void PlayerControllerComponent::Update(float deltaTime)
{
	//check input
	m_AccuShotTime += deltaTime;
	if (InputManager::GetInstance().IsBindingTriggered(m_MoveLeftId))
	{
		Transform t = m_pObject.lock()->GetTransform();
		Position2D p = t.GetPosition();
		p.x -= m_FlySpeed * deltaTime;
		if (p.x < m_LeftWindowLimit)
		{
			p.x = m_LeftWindowLimit;
		}
		t.SetPosition(p);
		m_pObject.lock()->SetTransform(t);
	}
	if (InputManager::GetInstance().IsBindingTriggered(m_MoveRightId))
	{
		Transform t = m_pObject.lock()->GetTransform();
		Position2D p = t.GetPosition();
		p.x += m_FlySpeed * deltaTime;
		if (p.x > m_RightWindowLimit)
		{
			p.x = m_RightWindowLimit;
		}
		t.SetPosition(p);
		m_pObject.lock()->SetTransform(t);
	}
	if (InputManager::GetInstance().IsBindingTriggered(m_ShootId))
	{
		if (m_AccuShotTime >= m_ShootCD)
		{
			m_AccuShotTime = 0.f;
			std::cout << "pew\n";
		}
	}

	//check collision
	//bulletmanager.got hit by bullets(hitbox)
	//enemymanager.got hit by enemies(hitbox)
}
