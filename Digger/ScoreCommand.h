#pragma once
#include "GOCommand.h"
#include "Player.h"
#include "SoundServiceLocator.h"
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
		if (m_pGameObject)
		{
			m_pGameObject->GetComponent<Player>()->Score(m_ScorePerTrigger);
			auto& soundService = SoundServiceLocator::Get_Sound_System();
			soundService.Play(1, 50);
		}
	}
private:
	int m_ScorePerTrigger;
};