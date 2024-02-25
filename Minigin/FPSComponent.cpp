#include "FPSComponent.h"
#include <string>

dae::FPSComponent::FPSComponent(GameObject* pOwner)
	:Component(pOwner)
	, m_FPS(0)
	, m_timer(0.f)
	//, m_FPSPerSec(0)
{
}

dae::FPSComponent::~FPSComponent()
{
	m_pOwnersTextComponent = nullptr; //not necessary i think?
}

void dae::FPSComponent::Update(float deltaTime)
{
	m_timer += deltaTime;
	++m_FPS;
	if(m_timer >= 1.f)
	{
		m_timer -= 1.f;
		if(m_pOwnersTextComponent)
		{
			std::string outputFpsString(std::to_string(m_FPS) + " FPS");
			m_pOwnersTextComponent->SetText(outputFpsString);
		}

		else if (m_pOwnersTextComponent == nullptr && GetGameObject()->GetComponent<TextComponent>())//check if we dont have a textComponent yet, and if owner has one
		{
			
			m_pOwnersTextComponent = GetGameObject()->GetComponent<TextComponent>();
		}
		else
		{
			std::cout << "logic error in FPSComponent, a GameObject has ran into the final option of Update" << std::endl;
		}
		m_FPS = 0;

	}
}

int dae::FPSComponent::GetFPS() const
{
	return m_FPS;
}
