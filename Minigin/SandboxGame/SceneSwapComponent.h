#pragma once
#include <BaseComponent.h>
#include "Gamemode.h"

class SceneSwapComponent : public minigin::BaseComponent
{
public:
	SceneSwapComponent(const std::weak_ptr<minigin::Object>& object, const std::string& sceneName, const std::string& componentName = "none");
	virtual ~SceneSwapComponent() = default;
	SceneSwapComponent(const SceneSwapComponent& other) = delete;
	SceneSwapComponent(SceneSwapComponent&& other) = delete;
	SceneSwapComponent& operator=(const SceneSwapComponent& other) = delete;
	SceneSwapComponent& operator=(SceneSwapComponent&& other) = delete;

	virtual void Update([[maybe_unused]]float deltaTime) override {};
	virtual void Render() override {};
	void Swap() const;
	//void Swap(Gamemode gamemode, bool reload) const;
private:
	std::string m_SceneName;
};

