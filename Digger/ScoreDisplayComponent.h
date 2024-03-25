#pragma once
#include "Component.h"
#include "IObserver.h"
#include "Player.h"
#include "TextComponent.h"

using namespace dae;
class ScoreDisplayComponent : public Component, public IObserver<int> 
{
public:
	ScoreDisplayComponent(GameObject* pOwner, Player* pObservedPlayerComp);
	~ScoreDisplayComponent();
	void OnNotify(int stat) override;
private:

	void UpdateDisplay(int stat); //helper function bc frequently used
	TextComponent* m_pTextComponent; //dont delete, not parent
	Player* m_pPlayerComp; //dont delete, not parent
};


