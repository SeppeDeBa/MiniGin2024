#include "ScoreDisplayComponent.h"
#include <sstream>
#include <iomanip>

#include "SoundServiceLocator.h"


ScoreDisplayComponent::ScoreDisplayComponent(dae::GameObject* pOwner)
		: Component(pOwner)

	{
		m_pTextComponent = pOwner->GetComponent<dae::TextComponent>();
		UpdateDisplay(m_Score);
	}


	void ScoreDisplayComponent::OnNotify(ScoreType type)
	{
		m_Score += static_cast<int>(type);
		if(type == ScoreType::EMERALDS)
		{
			++m_GemCombo;
			if(m_GemCombo >= m_GemsRequiredForCombo)
			{
				m_GemCombo = 0;
				OnNotify(ScoreType::EMERALDCOMBO);
			}
		}
		UpdateDisplay(m_Score);
		auto& soundService = SoundServiceLocator::Get_Sound_System();
		soundService.Play(1, 50);
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
