#include "MiniginPCH.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "Object.h"

#include <SDL.h>
#include <SDL_ttf.h>

using namespace minigin;

TextComponent::TextComponent(const std::weak_ptr<Object>& object, const std::string& text, const std::string& filepath, int fontSize, const std::string& componentName)
	:TextComponent(object, text, filepath, fontSize, 255, 255, 255, componentName)
{
}

TextComponent::TextComponent(const std::weak_ptr<Object>& object, const std::string& text, const std::string& filepath, int fontSize, int r, int g, int b, const std::string& componentName)
	:BaseComponent(object, componentName)
	, m_pFont{ nullptr }
	, m_pTexture{}
	, m_Text{ text }
	, m_Transform{}
	, m_IsVisible{ true }
{
	m_pFont = ResourceManager::GetInstance().LoadFont(filepath, fontSize);

	const SDL_Color color = { Uint8(r), Uint8(g), Uint8(b) };
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_pTexture = std::make_shared<Texture2D>(texture);

	//offset transform to center texture
	int width{};
	int height{};
	Renderer::GetInstance().GetTextureSize(*m_pTexture, width, height);
	m_Transform.SetPosition(Position2D{ -(float(width) / 2.f), -(float(height) / 2.f) });
}

void TextComponent::Render()
{
	if (m_pTexture != nullptr && m_IsVisible)
	{
		Transform objTrans{ m_pObject.lock()->GetTransform() };
		Renderer::GetInstance().RenderTexture(*m_pTexture, objTrans.GetPosition().x + m_Transform.GetPosition().x, objTrans.GetPosition().y + m_Transform.GetPosition().y);
	}
}

const Transform& TextComponent::GetTransform() const
{
	return m_Transform;
}

void TextComponent::SetTransform(const Transform& transform)
{
	m_Transform = transform;
}

void TextComponent::SetVisible(bool isVisible)
{
	m_IsVisible = isVisible;
}
