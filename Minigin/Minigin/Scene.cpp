#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Object.h"

using namespace minigin;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_SceneObjects.push_back(object);
}

void Scene::Add(const std::shared_ptr<Object>& object)
{
	m_Objects.push_back(object);
}

const std::string& minigin::Scene::GetName() const
{
	return m_Name;
}

void Scene::Update(float deltaTime)
{
	for(auto& sceneObject : m_SceneObjects)
	{
		sceneObject->Update();
	}
	for (auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& sceneObject : m_SceneObjects)
	{
		sceneObject->Render();
	}
	for (auto& object : m_Objects)
	{
		object->Render();
	}
}

