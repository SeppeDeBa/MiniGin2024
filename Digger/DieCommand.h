#pragma once
#include "GOCommand.h"
#include "Player.h"


class DieCommand : public dae::GOCommand
{
public:
	DieCommand(dae::GameObject* gameObjPtr)
		: GOCommand(gameObjPtr)
	{
		
	}
	virtual ~DieCommand() = default;

	void Execute(float) override
	{
		if (m_pGameObject) m_pGameObject->GetComponent<Player>()->Die();
	}
};

