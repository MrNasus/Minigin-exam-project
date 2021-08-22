#include "SceneSwapComponent.h"
#include "SceneManager.h"
#include "SandboxGame.h"

using namespace minigin;

SceneSwapComponent::SceneSwapComponent(const std::weak_ptr<minigin::Object>& object, const std::string& sceneName, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_SceneName(sceneName)
{
}

void SceneSwapComponent::Swap() const
{
	SceneManager::GetInstance().SetCurrentScene(m_SceneName);
}

//void SceneSwapComponent::Swap(Gamemode gamemode, bool reload) const
//{
//	if (m_SceneName == "Game")
//	{
//
//	}
//	SceneManager::GetInstance().SetCurrentScene(m_SceneName);
//}
