#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

dae::Scene& dae::SceneManager::GetScene(const std::string& name)
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
