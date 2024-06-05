#include "ScoreDisplayComponent.h"
#include <sstream>
#include <iomanip>
namespace dae
{

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

	void ScoreDisplayComponent::OnNotify(int scoreGained)
	{
		m_Score += scoreGained;
		UpdateDisplay(m_pPlayerComp->GetScore());
	}

	void ScoreDisplayComponent::AssignPlayerOne(Player* pPlayerOneComponent)
	{
		if (m_pPlayerComp)
		{
			m_pPlayerComp->scoreChanged.RemoveObserver(this);
		}
		m_pPlayerComp = pPlayerOneComponent;
		m_pPlayerComp->scoreChanged.AddObserver(this);
	}

	void ScoreDisplayComponent::AssignPlayerTwo(Player* pPlayerTwoComponent)
	{
		if (m_pPlayerTwoComp)
		{
			m_pPlayerTwoComp->scoreChanged.RemoveObserver(this);
		}
		m_pPlayerTwoComp = pPlayerTwoComponent;
		m_pPlayerTwoComp->scoreChanged.AddObserver(this);
	}

	void ScoreDisplayComponent::UpdateDisplay(int stat)
	{
		if (m_pTextComponent)
		{
			std::ostringstream oss;
			oss << std::setw(6) << std::setfill('0') << stat;
			m_pTextComponent->SetText(oss.str());
		}
		else 
		{
			std::cout << "a GameStatsDisplay does not have a pTextComponent to find" << std::endl;
		}
	}
}