#include "SceneSwapComponent.h"
#include "SceneManager.h"

using namespace minigin;

SceneSwapComponent::SceneSwapComponent(const std::shared_ptr<minigin::Object>& object, const std::string& sceneName, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_SceneName(sceneName)
{
}

void SceneSwapComponent::Swap() const
{
	SceneManager::GetInstance().SetCurrentScene(m_SceneName);
}
