#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Object.h"

using namespace minigin;

TextureComponent::TextureComponent(const std::shared_ptr<Object>& object, const std::string& filename, const std::string& componentName)
	: BaseComponent{ object, componentName}
	, m_pTexture{ ResourceManager::GetInstance().LoadTexture(filename) }
	, m_IsVisible{true}
	, m_Transform{}
{
	//offset transform to center texture
	int width{};
	int height{};
	Renderer::GetInstance().GetTextureSize(*m_pTexture, width, height);
	m_Transform.SetPosition(Position2D{ -(float(width) / 2.f), -(float(height) / 2.f) });
}

void TextureComponent::Render()
{
	if (m_pTexture != nullptr && m_IsVisible)
	{
		Transform objTrans{ m_pObject->GetTransform() };
		Renderer::GetInstance().RenderTexture(*m_pTexture, objTrans.GetPosition().x + m_Transform.GetPosition().x, objTrans.GetPosition().y + m_Transform.GetPosition().y);
	}
}

const Transform& TextureComponent::GetTransform() const
{
	return m_Transform;
}

void TextureComponent::SetTransform(const Transform& transform)
{
	m_Transform = transform;
}

void TextureComponent::SetVisible(bool isVisible)
{
	m_IsVisible = isVisible;
}
