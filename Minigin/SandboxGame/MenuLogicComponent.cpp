#include "MenuLogicComponent.h"
#include "Object.h"
#include "InputManager.h"

using namespace minigin;

MenuLogicComponent::MenuLogicComponent(const std::shared_ptr<minigin::Object>& object,const std::vector<std::shared_ptr<minigin::Object>>& buttons, const std::string& componentName)
	:BaseComponent(object, componentName)
	,m_ActiveButton{}
	,m_pActiveButtonVisuals{}
	,m_pInactiveButtonVisuals{}
	,m_pButtons{}
{
	for (size_t i{}; i < buttons.size(); ++i)
	{
		m_pButtons.push_back(buttons[i]->GetComponent<SceneSwapComponent>());
		m_pActiveButtonVisuals.push_back(buttons[i]->GetComponent<TextComponent>("SelectedVisual"));
		m_pInactiveButtonVisuals.push_back(buttons[i]->GetComponent<TextComponent>("UnselectedVisual"));
		if (i == 0)
		{
			m_pActiveButtonVisuals[i]->SetVisible(true);
			m_pInactiveButtonVisuals[i]->SetVisible(false);
		}
		else
		{
			m_pActiveButtonVisuals[i]->SetVisible(false);
			m_pInactiveButtonVisuals[i]->SetVisible(true);
		}

	}

	InputBinding bindingUp{ 0, InputTriggerState::Pressed, ControllerButton::DpadUp, KeyboardButton::Up };
	InputManager::GetInstance().AddInputBinding(bindingUp);
	InputBinding bindingDown{ 1, InputTriggerState::Pressed, ControllerButton::DpadDown, KeyboardButton::Down };
	InputManager::GetInstance().AddInputBinding(bindingDown);
	InputBinding bindingSelect{ 2, InputTriggerState::Released, ControllerButton::ButtonA, KeyboardButton::Space };
	InputManager::GetInstance().AddInputBinding(bindingSelect);
}

void MenuLogicComponent::Awake()
{
}

void MenuLogicComponent::Update([[maybe_unused]] float deltaTime)
{
	if (InputManager::GetInstance().IsBindingTriggered(0)) //up
	{
		m_pActiveButtonVisuals[m_ActiveButton]->SetVisible(false);
		m_pInactiveButtonVisuals[m_ActiveButton]->SetVisible(true);
		--m_ActiveButton;
		if (m_ActiveButton < 0)
		{
			m_ActiveButton = m_pButtons.size() - 1;
		}
		m_pActiveButtonVisuals[m_ActiveButton]->SetVisible(true);
		m_pInactiveButtonVisuals[m_ActiveButton]->SetVisible(false);
	}
	if (InputManager::GetInstance().IsBindingTriggered(1)) //down
	{
		m_pActiveButtonVisuals[m_ActiveButton]->SetVisible(false);
		m_pInactiveButtonVisuals[m_ActiveButton]->SetVisible(true);
		++m_ActiveButton;
		m_ActiveButton %= m_pButtons.size();
		m_pActiveButtonVisuals[m_ActiveButton]->SetVisible(true);
		m_pInactiveButtonVisuals[m_ActiveButton]->SetVisible(false);
	}
	if (InputManager::GetInstance().IsBindingTriggered(2)) //select
	{
		m_pButtons[m_ActiveButton]->Swap();
	}
}

