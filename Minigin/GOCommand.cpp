#include "GOCommand.h"

dae::GOCommand::GOCommand(GameObject* gameObjPtr)
	:m_pGameObject(gameObjPtr)
{
}

dae::GOCommand::~GOCommand()
{
	m_pGameObject = nullptr;
}

