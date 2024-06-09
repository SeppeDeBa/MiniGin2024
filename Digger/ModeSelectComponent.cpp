#include "ModeSelectComponent.h"


ModeSelectComponent::ModeSelectComponent(dae::GameObject* pOwner, Level* pLevelToStart)
	:dae::Component(pOwner)
{
	dae::TextComponent* onwerTextCompPtr = GetGameObject()->GetComponent<dae::TextComponent>();
	if (onwerTextCompPtr) m_pTextComponent = onwerTextCompPtr;
	else
	{
		std::cout << "modeSelector doesnt have text component" << std::endl;
	}
	m_pLevel = pLevelToStart;

	m_InitControls();
	m_UpdateDisplayToCurrentGM();
}

ModeSelectComponent::~ModeSelectComponent()
{

}

void ModeSelectComponent::SelectNextGameMode()
{
	switch(m_currentGamemode)
	{
	case SOLO:
		m_currentGamemode = DUO;
		break;
	case DUO:
		m_currentGamemode = VS;
		break;
	case VS:
		m_currentGamemode = SOLO;
		break;
	default:
		m_currentGamemode = SOLO;
	}
	m_UpdateDisplayToCurrentGM();
}

void ModeSelectComponent::SelectPreviousGameMode()
{
	switch (m_currentGamemode)
	{
	case SOLO:
		m_currentGamemode = VS;
		break;
	case DUO:
		m_currentGamemode = SOLO;
		break;
	case VS:
		m_currentGamemode = DUO;
		break;
	default:
		m_currentGamemode = SOLO;

	}
	m_UpdateDisplayToCurrentGM();
}

void ModeSelectComponent::ConfirmGameMode()
{
	auto& input = dae::InputManager::GetInstance();
	const unsigned int controllerOne{ 0 };
	input.ClearConsoleCommandsForIndex(controllerOne);

	switch(m_currentGamemode)
	{
	case SOLO:
		break;
	case DUO:
		m_pLevel->ActivateCoop();
		break;
	case VS:
		m_pLevel->ActivateVersus();
		break;
	default:
		break;
	}
	m_pLevel->StartGame();

}

std::string ModeSelectComponent::m_GetStringFromCurrentMode() const
{
	std::string outputString{};
	switch (m_currentGamemode)
	{
	case SOLO:
		outputString = "Single Player";
		break;
	case DUO:
		outputString = "Co-Op Gameplay";
		break;
	case VS:
		outputString = "Versus Play";
		break;
	default:
		outputString = "Single Player";
	}
	return outputString;
}

void ModeSelectComponent::m_UpdateDisplay(const std::string& outputString)
{
	std::string finalOutputString{ "(DPAD) " };
	finalOutputString += outputString;
	if (m_pTextComponent)m_pTextComponent->SetText(outputString);
}

void ModeSelectComponent::m_UpdateDisplayToCurrentGM()
{
	m_UpdateDisplay(m_GetStringFromCurrentMode());
}

void ModeSelectComponent::m_InitControls()
{
	auto& input = dae::InputManager::GetInstance();
	const unsigned int controllerOne{ 0 };
	//next
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DpadUp,
		std::make_unique<GamemodeSelectorCommand>(this, 1), dae::InputType::ISDOWN);
	//previous
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DPadDown,
		std::make_unique<GamemodeSelectorCommand>(this, -1), dae::InputType::ISDOWN);
	//select
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::ButtonA,
		std::make_unique<GamemodeSelectorCommand>(this, 0), dae::InputType::ISDOWN);
}
