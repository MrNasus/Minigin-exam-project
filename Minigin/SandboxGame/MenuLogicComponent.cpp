#include "MenuLogicComponent.h"

using namespace minigin;

MenuLogicComponent::MenuLogicComponent(const std::shared_ptr<minigin::Object>& object, std::vector<std::weak_ptr<minigin::Object>> buttons, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_pButtons(buttons)
{
}

void MenuLogicComponent::Update(float deltaTime)
{
}
