#pragma once
#include "GOCommand.h"
#include "Player.h"
class ScoreCommand : public dae::GOCommand
{
public:
	ScoreCommand(dae::GameObject* gameObjPtr, int scoreChange = 100)
		: GOCommand(gameObjPtr)
		,m_ScorePerTrigger(scoreChange)
	{
		
	}
	virtual ~ScoreCommand() = default;


	void Execute(float) override
	{
		if (m_pGameObject) m_pGameObject->GetComponent<Player>()->Score(m_ScorePerTrigger);
	}
private:
	int m_ScorePerTrigger;
};