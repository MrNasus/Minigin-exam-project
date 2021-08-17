#include "MiniginPCH.h"
#include "Scene.h"
#include "Object.h"

using namespace minigin;


Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

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
	for (auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (auto& object : m_Objects)
	{
		object->Render();
	}
}

