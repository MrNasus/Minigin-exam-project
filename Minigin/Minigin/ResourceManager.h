#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <string>

namespace minigin
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		const std::shared_ptr<Texture2D>& LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_pTextures{};
	};
}
