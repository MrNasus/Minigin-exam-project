#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "ServiceLocator.h"

using namespace minigin;

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);

	SceneManager* sceneManager = ServiceLocator<SceneManager>::getService();
	sceneManager->Render();
	
	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void minigin::Renderer::GetTextureSize(const Texture2D& texture, int& width, int& height) const
{
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &width, &height);
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, const Rectangle& dst) const
{
	SDL_Rect dstRect;
	dstRect.x = static_cast<int>(dst.x);
	dstRect.y = static_cast<int>(dst.y);
	dstRect.w = static_cast<int>(dst.width);
	dstRect.h = static_cast<int>(dst.height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dstRect);
}

void Renderer::RenderTexture(const Texture2D& texture, const Rectangle& src, const Rectangle& dst) const
{
	RenderTexture(texture, src, dst, 0.f);
}

void Renderer::RenderTexture(const Texture2D& texture, const Rectangle& src, const Rectangle& dst, float angleDEG) const
{
	SDL_Rect srcRect;
	srcRect.x = static_cast<int>(src.x);
	srcRect.y = static_cast<int>(src.y);
	srcRect.w = static_cast<int>(src.width);
	srcRect.h = static_cast<int>(src.height);

	SDL_Rect dstRect;
	dstRect.x = static_cast<int>(dst.x);
	dstRect.y = static_cast<int>(dst.y);
	dstRect.w = static_cast<int>(dst.width);
	dstRect.h = static_cast<int>(dst.height);

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect, angleDEG, nullptr, SDL_FLIP_NONE);
}
