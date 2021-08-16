#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
#include <memory>

namespace minigin
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& GetScene(const std::string& name);

		void Update(float deltaTime);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
