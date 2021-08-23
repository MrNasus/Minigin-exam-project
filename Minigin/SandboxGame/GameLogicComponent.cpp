#include "GameLogicComponent.h"
#include "InputManager.h"
#include "SceneSwapComponent.h"
#include "Object.h"

using namespace minigin;

GameLogicComponent::GameLogicComponent(const std::weak_ptr<minigin::Object>& object, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_PlayerShotsFired{}
	,m_PlayerShotsMissed{}
	,m_TotalScore{}
{
	InputBinding bindingPause{ 9, InputTriggerState::Pressed, ControllerButton::ButtonStart, KeyboardButton::Escape };
	InputManager::GetInstance().AddInputBinding(bindingPause);
}

void GameLogicComponent::Update([[maybe_unused]]float deltaTime)
{
	if (InputManager::GetInstance().IsBindingTriggered(9))
	{
		m_pObject.lock()->GetComponent<SceneSwapComponent>()->Swap();
	}

}
