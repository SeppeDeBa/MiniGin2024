#pragma once
#include "Component.h"
#include "IObserver.h"
#include "Player.h"
#include "TextComponent.h"
#include <vector>
class Level;

class LivesDisplayComponent : public dae::Component, public IObserver<int>
{
public:
	LivesDisplayComponent(dae::GameObject* pOwner, Level* pLevel);
	~LivesDisplayComponent() override = default;
	void OnNotify(int) override;
	void Reset();
private:

	void m_UpdateDisplay(int stat); 
	dae::TextComponent* m_pTextComponent; //dont delete, not parent
	Level* m_pLevel{};

	int m_LivesRemaining{ 3 };
	const int m_StartingLives{ 3 };
};




