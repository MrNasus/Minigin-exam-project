#include "GameLogicComponent.h"

GameLogicComponent::GameLogicComponent(const std::weak_ptr<minigin::Object>& object, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_PlayerShotsFired{}
	,m_PlayerShotsMissed{}
	,m_TotalScore{}
{
}
