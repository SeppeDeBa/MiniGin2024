#include "BagState.h"
#include "BagComponent.h"
//===NEUTRAL===
void NeutralState::OnEnter()
{
	m_CanBePushed = true;
}

void NeutralState::OnExit()
{
	m_CanBePushed = false;
}

//===SHAKING===
void ShakingState::Update(float deltaTime)
{
	m_ShakeTimer += deltaTime;
	UpdateVisuals();
}

void ShakingState::OnEnter()
{
	m_ShakeTimer = 0.f;
}

void ShakingState::OnExit()//reset visuals to neutral state
{
	m_pBag->SetTextureByRotation(BagRotation::NEUTRAL);
}

void ShakingState::UpdateVisuals()
{
	if (m_ShakeTimer > 1.5f) m_pBag->SetTextureByRotation(BagRotation::RIGHT);
	else if (m_ShakeTimer > 1.f) m_pBag->SetTextureByRotation(BagRotation::NEUTRAL);
	else if (m_ShakeTimer > 0.5f) m_pBag->SetTextureByRotation(BagRotation::LEFT);
	else if (m_ShakeTimer > 0.f) m_pBag->SetTextureByRotation(BagRotation::NEUTRAL);
}


