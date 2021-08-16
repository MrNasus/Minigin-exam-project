#include "MiniginPCH.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

#include <SDL.h>
#include <SDL_ttf.h>

using namespace minigin;

TextComponent::TextComponent(const std::shared_ptr<Object>& object, const std::string& text, const std::string& filepath, int fontSize)
	:TextComponent(object, text, filepath, fontSize, 255, 255, 255)
{
}

TextComponent::TextComponent(const std::shared_ptr<Object>& object, const std::string& text, const std::string& filepath, int fontSize, int r, int g, int b)
	:BaseComponent(object)
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
}

void TextComponent::Render()
{
	if (m_pTexture != nullptr && m_IsVisible)
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
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

void TextComponent::SetTextVisible(bool isVisible)
{
	m_IsVisible = isVisible;
}
