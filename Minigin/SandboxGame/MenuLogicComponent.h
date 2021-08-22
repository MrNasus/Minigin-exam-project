#pragma once
#include <BaseComponent.h>
#include <vector>

class MenuLogicComponent : public minigin::BaseComponent
{
public:
	MenuLogicComponent(const std::shared_ptr<minigin::Object>& object, std::vector<std::weak_ptr<minigin::Object>> buttons, const std::string& componentName = "none");
	virtual ~MenuLogicComponent() = default;
	MenuLogicComponent(const MenuLogicComponent& other) = delete;
	MenuLogicComponent(MenuLogicComponent&& other) = delete;
	MenuLogicComponent& operator=(const MenuLogicComponent& other) = delete;
	MenuLogicComponent& operator=(MenuLogicComponent&& other) = delete;

	virtual void Awake() override {};
	virtual void Update(float deltaTime) override;
	virtual void Render() override {};
private:
	std::vector<std::weak_ptr<minigin::Object>> m_pButtons;
};

