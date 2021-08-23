#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Texture2D.h"
#include <SDL.h>

using namespace minigin;

SpriteComponent::SpriteComponent(const std::weak_ptr<Object>& object, const std::string& filename, int nrOfFrames, float loopTime, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_AccuSec{}
	,m_CurrentFrame{}
	,m_FrameWidth{}
	,m_FrameHeight{}
	,m_IsVisible{true}
	,m_NrOfFrames{nrOfFrames}
	,m_pTexture{ ResourceManager::GetInstance().LoadTexture(filename) }
	,m_SecPerFrame{loopTime / nrOfFrames}
	,m_TextureHeight{}
	,m_TextureWidth{}
	,m_Transform{}
{
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_TextureWidth, &m_TextureHeight);
	m_FrameWidth = m_TextureWidth / m_NrOfFrames;
	m_FrameHeight = m_TextureHeight;

	//offset transform to center texture
	m_Transform.SetPosition(Position2D{ -(float(m_FrameWidth) / 2.f), -(float(m_FrameHeight) / 2.f) });

}

void SpriteComponent::Update(float deltaTime)
{
	m_AccuSec += deltaTime;

	if (m_AccuSec >= m_SecPerFrame)
	{
		++m_CurrentFrame;
		m_CurrentFrame %= m_NrOfFrames;

		m_AccuSec -= m_SecPerFrame;
	}
}

void SpriteComponent::Render()
{
	if (m_pTexture != nullptr && m_IsVisible)
	{
		Transform objTrans{ m_pObject.lock()->GetTransform() };
		Rectangle dst = { objTrans.GetPosition().x + m_Transform.GetPosition().x, objTrans.GetPosition().y + m_Transform.GetPosition().y, float(m_FrameWidth), float(m_FrameHeight) };
		Rectangle src = { float(m_FrameWidth * m_CurrentFrame), 0.f, float(m_FrameWidth), float(m_FrameHeight) };
		
		Renderer::GetInstance().RenderTexture(*m_pTexture, src, dst, m_Transform.GetRotation().z + objTrans.GetRotation().z);
	}
}

const Transform& SpriteComponent::GetTransform() const
{
	return m_Transform;
}

void SpriteComponent::SetTransform(const Transform& transform)
{
	m_Transform = transform;
}

int SpriteComponent::GetFrameHeight() const
{
	return m_FrameHeight;
}

int SpriteComponent::GetFrameWidth() const
{
	return m_FrameWidth;
}

float SpriteComponent::GetTextureHeight() const
{
	return float(m_TextureHeight);
}

void SpriteComponent::SetFrameHeight(int height)
{
	m_FrameHeight = height;
}

void SpriteComponent::SetVisible(bool isVisible)
{
	m_IsVisible = isVisible;
}

void SpriteComponent::ResetClock()
{
	m_AccuSec = 0.f;
}