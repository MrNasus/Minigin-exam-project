#pragma once
#include <BaseComponent.h>
class GameLogicComponent : public minigin::BaseComponent
{
public:
	GameLogicComponent(const std::weak_ptr<minigin::Object>& object, const std::string& componentName = "none");
	virtual ~GameLogicComponent() = default;
	GameLogicComponent(const GameLogicComponent& other) = delete;
	GameLogicComponent(GameLogicComponent&& other) = delete;
	GameLogicComponent& operator=(const GameLogicComponent& other) = delete;
	GameLogicComponent& operator=(GameLogicComponent&& other) = delete;

	virtual void Update([[maybe_unused]] float deltaTime) override {};
	virtual void Render() override {};

private:
	unsigned int m_TotalScore;
	unsigned int m_PlayerShotsFired;
	unsigned int m_PlayerShotsMissed;
};

