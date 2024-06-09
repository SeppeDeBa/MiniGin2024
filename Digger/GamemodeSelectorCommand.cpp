#include "GamemodeSelectorCommand.h"
#include "ModeSelectComponent.h"

GamemodeSelectorCommand::GamemodeSelectorCommand(ModeSelectComponent* pModeSelector, int inputType)
{
	m_pModeSelectComp = pModeSelector;
	m_inputType = inputType;
}

void GamemodeSelectorCommand::Execute(float)
{
	switch(m_inputType)
	{
	case 0:
		m_pModeSelectComp->ConfirmGameMode();
		break;
	case 1:
		m_pModeSelectComp->SelectNextGameMode();
		break;
	case -1:
		m_pModeSelectComp->SelectPreviousGameMode();
		break;
	default:
		break;
	}
}
