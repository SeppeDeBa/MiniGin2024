#pragma once
#include "Component.h"
#include "IObserver.h"
#include "Player.h"
#include "TextComponent.h"
#include <vector>

namespace dae
{

	class LivesDisplayComponent : public Component, public IObserver<int>
	{
	public:
		LivesDisplayComponent(GameObject* pOwner, Player* pObservedPlayerComp);
		~LivesDisplayComponent();
		void OnNotify(int) override;
	private:

		void UpdateDisplay(int stat); //helper function bc frequently used
		TextComponent* m_pTextComponent; //dont delete, not parent
		Player* m_pPlayerComp; //dont delete, not parent
	};
}

