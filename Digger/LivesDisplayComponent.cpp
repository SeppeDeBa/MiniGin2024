#include "LivesDisplayComponent.h"
namespace dae
{

	LivesDisplayComponent::LivesDisplayComponent(GameObject* pOwner, Player* pObservedPlayerComp)
		: Component(pOwner)
		, m_pPlayerComp(pObservedPlayerComp)
	{
		m_pPlayerComp->playerDied.AddObserver(this);
		m_pTextComponent = pOwner->GetComponent<TextComponent>();
		UpdateDisplay(m_pPlayerComp->GetLives());
	}

	LivesDisplayComponent::~LivesDisplayComponent()
	{
		if (m_pPlayerComp)
		{
			m_pPlayerComp->playerDied.RemoveObserver(this); //automise with destructor on other side, does it have a point? todo: ask
		}
	}

	void LivesDisplayComponent::OnNotify(int)
	{
		UpdateDisplay(m_pPlayerComp->GetLives());
	}

	void LivesDisplayComponent::UpdateDisplay(int stat)
	{
		if (m_pTextComponent)
		{
			m_pTextComponent->SetText("Lives: " + std::to_string(stat));
		}
		else //should i put a replace textComp ptr here, or just get it whenever score updates?
		{
			std::cout << "a GameStatsDisplay does not have a pTextComponent to find" << std::endl;
		}
	}

}