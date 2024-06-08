#include "SkipLevelCommand.h"
#include "Level.h"

void SkipLevelCommand::Execute(float)
{
	m_pLevel->GoToNextLevel();
}
