#include "GameOverScreenComponent.h"
#include "Object.h"
#include "SceneSwapComponent.h"

using namespace minigin;

GameOverScreenComponent::GameOverScreenComponent(const std::weak_ptr<minigin::Object>& object, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_AccuWaitSec{0.f}
	,m_WaitTime{3.f}
{
}

void GameOverScreenComponent::Update(float deltaTime)
{
	m_AccuWaitSec += deltaTime;
	if (m_AccuWaitSec >= m_WaitTime)
	{
		m_AccuWaitSec = 0.f;
		m_pObject.lock()->GetComponent<SceneSwapComponent>()->Swap();
	}
}
