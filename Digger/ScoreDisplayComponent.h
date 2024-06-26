#pragma once
#include "Component.h"
#include "IObserver.h"
#include "Player.h"
#include "TextComponent.h"
#include <vector>
#include "ScoreTypeEnum.h"



class ScoreDisplayComponent final : public dae::Component, public IObserver<ScoreType>
{
public:
	ScoreDisplayComponent(dae::GameObject* pOwner);
	~ScoreDisplayComponent() override = default; //will not get deleted untill end of game cycle so no need for destructor to subscribe/unsubscribe
	void OnNotify(ScoreType type) override;
	void Reset();
	//void AssignPlayerOne(Player* pPlayerOneComponent);
	//void AssignPlayerTwo(Player* pPlayerTwoComponent);
private:

	void m_UpdateDisplay(int stat); //helper function
	dae::TextComponent* m_pTextComponent; //dont delete, not parent

	int m_Score{ 0 };
	unsigned int m_GemCombo{ 0 };
	const unsigned int m_GemsRequiredForCombo{ 8 };
};



