#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Texture2D.h"
#include <SDL.h>

using namespace minigin;

SpriteComponent::SpriteComponent(const std::shared_ptr<Object>& object, const std::string& filename, int nrOfFrames, float loopTime)
	:BaseComponent(object)
	,m_AccuSec{}
	,m_CurrentFrame{}
	,m_FrameWidth{}
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
		Transform objTrans{ m_pObject->GetTransform() };
		Rectangle dst = { objTrans.GetPosition().x + m_Transform.GetPosition().x, objTrans.GetPosition().y + m_Transform.GetPosition().y, float(m_FrameWidth), float(m_TextureHeight) };
		Rectangle src = { float(m_FrameWidth * m_CurrentFrame), 0.f, float(m_FrameWidth), float(m_TextureHeight) };
		
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

void SpriteComponent::SetVisible(bool isVisible)
{
	m_IsVisible = isVisible;
}
