#pragma once
#include "Singleton.h"
#include "HitboxStruct.h"

struct SDL_Window;
struct SDL_Renderer;

namespace minigin
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		Renderer(const Renderer & other) = delete;
		Renderer(Renderer && other) = delete;
		Renderer& operator=(const Renderer & other) = delete;
		Renderer& operator=(Renderer && other) = delete;

		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void GetTextureSize(const Texture2D& texture, int& width, int& height) const;

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, const Rectangle& dst) const;
		void RenderTexture(const Texture2D& texture, const Rectangle& src, const Rectangle& dst) const;
		void RenderTexture(const Texture2D& texture, const Rectangle& src, const Rectangle& dst, float angleDEG) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
	};
}

