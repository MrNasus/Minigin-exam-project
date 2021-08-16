#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void minigin::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void minigin::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

minigin::Scene& minigin::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

minigin::Scene& minigin::SceneManager::GetScene(const std::string& name)
{
	for (size_t i{}; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i].get()->GetName() == name)
		{
			return *m_Scenes[i].get();
		}
	}
	return *m_Scenes[0].get();
}
