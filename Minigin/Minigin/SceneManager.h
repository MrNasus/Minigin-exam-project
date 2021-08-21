#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
#include <memory>

namespace minigin
{
	class Scene;
	class SceneManager final
	{
	public:
		SceneManager() = default;
		~SceneManager() = default;

		SceneManager(const SceneManager & other) = delete;
		SceneManager(SceneManager && other) = delete;
		SceneManager& operator=(const SceneManager & other) = delete;
		SceneManager& operator=(SceneManager && other) = delete;

		Scene& CreateScene(const std::string& name);
		Scene& GetScene(const std::string& name);

		void SetCurrentScene(const std::string& name);

		void Update(float deltaTime);
		void Render();
	private:
		std::vector<std::shared_ptr<Scene>> m_pScenes;
		std::shared_ptr<Scene> m_pCurrentScene;
	};
}
