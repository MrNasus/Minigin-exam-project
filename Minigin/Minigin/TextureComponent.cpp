#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "Renderer.h"
#include "Object.h"

using namespace minigin;

TextureComponent::TextureComponent(const std::shared_ptr<Object>& object, const std::string& filename)
	: BaseComponent{ object }
	, m_pTexture{ nullptr }
	, m_IsVisible{true}
	, m_Transform{}
{
	ResourceManager* resourceManager = ServiceLocator<ResourceManager>::getService();
	Renderer* renderer = ServiceLocator<Renderer>::getService();
	m_pTexture = resourceManager->LoadTexture(filename);

	//offset transform to center texture
	int width{};
	int height{};
	renderer->GetTextureSize(*m_pTexture, width, height);
	m_Transform.SetPosition(Position2D{ -(float(width) / 2.f), -(float(height) / 2.f) });
}

void TextureComponent::Render()
{
	if (m_pTexture != nullptr && m_IsVisible)
	{
		Renderer* renderer = ServiceLocator<Renderer>::getService();
		Transform objTrans{ m_pObject->GetTransform() };
		renderer->RenderTexture(*m_pTexture, objTrans.GetPosition().x + m_Transform.GetPosition().x, objTrans.GetPosition().y + m_Transform.GetPosition().y);
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
