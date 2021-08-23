#pragma once
#include <BaseComponent.h>
class GameOverScreenComponent : public minigin::BaseComponent
{
public:
	GameOverScreenComponent(const std::weak_ptr<minigin::Object>& object, const std::string& componentName = "none");
	virtual ~GameOverScreenComponent() = default;
	GameOverScreenComponent(const GameOverScreenComponent& other) = delete;
	GameOverScreenComponent(GameOverScreenComponent&& other) = delete;
	GameOverScreenComponent& operator=(const GameOverScreenComponent& other) = delete;
	GameOverScreenComponent& operator=(GameOverScreenComponent&& other) = delete;

	virtual void Update(float deltaTime) override;
	virtual void Render() override {};

private:
	float m_AccuWaitSec;
	float m_WaitTime;
};

