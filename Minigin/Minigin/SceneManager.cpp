#include "MiniginPCH.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Scene.h"

using namespace minigin;

void SceneManager::Update(float deltaTime)
{
	m_pCurrentScene->Update(deltaTime);
}

void SceneManager::Render()
{
	m_pCurrentScene->Render();
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i].get()->GetName() == name)
		{
			std::cout << std::string{ "scene with name: " + name + " already exists\n" };
			return *m_pScenes[i].get();
		}
	}
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_pScenes.push_back(scene);
	if (m_pCurrentScene == nullptr)
	{
		m_pCurrentScene = m_pScenes[0];
	}
	return *scene;
}

Scene& SceneManager::GetScene(const std::string& name)
{
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i].get()->GetName() == name)
		{
			return *m_pScenes[i].get();
		}
	}
	return *m_pScenes[0].get();
}

void SceneManager::SetCurrentScene(const std::string& name)
{
	if (name == "Quit")
	{
		InputManager::GetInstance().SetQuit(true);
	}
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i].get()->GetName() == name)
		{
			m_pCurrentScene = m_pScenes[i];
			return;
		}
	}
	std::cout << std::string{ "scene with name: " + name + " not found\n" };
}
