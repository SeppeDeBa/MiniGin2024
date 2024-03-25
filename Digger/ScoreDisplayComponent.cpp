#include "ScoreDisplayComponent.h"
ScoreDisplayComponent::ScoreDisplayComponent(GameObject* pOwner, Player* pObservedPlayerComp)
	: Component(pOwner)
	, m_pPlayerComp(pObservedPlayerComp)
{
	m_pPlayerComp->scoreChanged.AddObserver(this);
	m_pTextComponent = pOwner->GetComponent<TextComponent>();
	UpdateDisplay(m_pPlayerComp->GetScore());
}

ScoreDisplayComponent::~ScoreDisplayComponent()
{
	if (m_pPlayerComp)
	{
		m_pPlayerComp->scoreChanged.RemoveObserver(this); //automise with destructor on other side, does it have a point? todo: ask
	}
}

void ScoreDisplayComponent::OnNotify(int stat)
{
	UpdateDisplay(m_pPlayerComp->GetScore());
}

void ScoreDisplayComponent::UpdateDisplay(int stat)
{
	if (m_pTextComponent)
	{
		m_pTextComponent->SetText("Score: " + std::to_string(stat));
	}
	else //should i put a replace textComp ptr here, or just get it whenever score updates?
	{
		std::cout << "a GameStatsDisplay does not have a pTextComponent to find" << std::endl;
	}
}