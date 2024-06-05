#pragma once
#include "Component.h"
#include "IObserver.h"
#include "Player.h"
#include "TextComponent.h"
#include <vector>

namespace dae
{

	class ScoreDisplayComponent : public dae::Component, public IObserver<int>
	{
	public:
		ScoreDisplayComponent(dae::GameObject* pOwner, Player* pObservedPlayerComp);
		~ScoreDisplayComponent();
		void OnNotify(int scoreGained) override;
		void AssignPlayerOne(Player* pPlayerOneComponent);
		void AssignPlayerTwo(Player* pPlayerTwoComponent);
	private:

		void UpdateDisplay(int stat); //helper function bc frequently used
		dae::TextComponent* m_pTextComponent; //dont delete, not parent
		Player* m_pPlayerComp; //dont delete, not parent
		Player* m_pPlayerTwoComp;
		int m_Score{ 0 };
	};
}


