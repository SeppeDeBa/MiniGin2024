#include "LivesDisplayComponent.h"
#include "Level.h"
#include "SoundServiceLocator.h"

LivesDisplayComponent::LivesDisplayComponent(dae::GameObject* pOwner, Level* pLevel)
	: Component(pOwner)
{
	m_pTextComponent = pOwner->GetComponent<dae::TextComponent>();
	m_pLevel = pLevel;
	m_UpdateDisplay(m_LivesRemaining);
}

void LivesDisplayComponent::OnNotify(int)
{
	--m_LivesRemaining;
	if(m_LivesRemaining<0)
	{
		m_pLevel->EndGame();
		//kill player
	}
	else
	{
		m_UpdateDisplay(m_LivesRemaining);
		m_pLevel->ReloadLevel();
		auto& soundService = SoundServiceLocator::Get_Sound_System();
		soundService.Play(1, 50);
	}
}

void LivesDisplayComponent::Reset()
{
	m_LivesRemaining = m_StartingLives;
	m_UpdateDisplay(m_LivesRemaining);
}

void LivesDisplayComponent::m_UpdateDisplay(int stat)
{
	if(m_pTextComponent)
	{
		std::string outputString{ "Lives: "};
		outputString += std::to_string(stat);
		m_pTextComponent->SetText(outputString);
	}
}
