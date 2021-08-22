#pragma once
#include "BaseComponent.h"
#include <vector>
#include "TextComponent.h"
#include "SceneSwapComponent.h"

class MenuLogicComponent : public minigin::BaseComponent
{
public:
	MenuLogicComponent(const std::shared_ptr<minigin::Object>& object, const std::vector<std::shared_ptr<minigin::Object>>& buttons, const std::string& componentName = "none");
	virtual ~MenuLogicComponent() = default;
	MenuLogicComponent(const MenuLogicComponent& other) = delete;
	MenuLogicComponent(MenuLogicComponent&& other) = delete;
	MenuLogicComponent& operator=(const MenuLogicComponent& other) = delete;
	MenuLogicComponent& operator=(MenuLogicComponent&& other) = delete;

	virtual void Awake() override;
	virtual void Update([[maybe_unused]]float deltaTime) override;
	virtual void Render() override {};

private:
	std::vector<std::shared_ptr<SceneSwapComponent>> m_pButtons;
	std::vector<std::shared_ptr<minigin::TextComponent>> m_pActiveButtonVisuals;
	std::vector<std::shared_ptr<minigin::TextComponent>> m_pInactiveButtonVisuals;
	int m_ActiveButton;
};

