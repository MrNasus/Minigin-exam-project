#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

minigin::GameObject::~GameObject() = default;

void minigin::GameObject::Update(){}

void minigin::GameObject::Render() const
{
	const auto pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void minigin::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void minigin::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(Position2D{x, y});
}
