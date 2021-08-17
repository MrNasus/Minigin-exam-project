#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

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

void minigin::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void minigin::Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_Renderer);
}

void minigin::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void minigin::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	int w;
	int h;
	SDL_FRect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &w, &h);
	dst.w = static_cast<float>(w);
	dst.h = static_cast<float>(h);
	SDL_RenderCopyF(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void minigin::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_FRect dst;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_RenderCopyF(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void minigin::Renderer::RenderTexture(const Texture2D& texture, const Rectangle& src, const Rectangle& dst, float angleDEG) const
{
	SDL_Rect srcRect;
	srcRect.x = static_cast<int>(src.x);
	srcRect.y = static_cast<int>(src.y);
	srcRect.w = static_cast<int>(src.width);
	srcRect.h = static_cast<int>(src.height);

	SDL_FRect dstRect;
	dstRect.x = dst.x;
	dstRect.y = dst.y;
	dstRect.w = dst.width;
	dstRect.h = dst.height;

	SDL_RenderCopyExF(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect, angleDEG, nullptr, SDL_FLIP_NONE);
}
