#include "BagState.h"
#include "BagComponent.h"
#include <iostream>

//Base
BagState::BagState(BagComponent* pBag)
	:m_pBag(pBag)
{
}

//===NEUTRAL===
NeutralState::NeutralState(BagComponent* pBag)
	:BagState(pBag)
{
}

void NeutralState::Update(float)
{
}

void NeutralState::OnEnter()
{

}

void NeutralState::OnExit()
{
	
}

//===SHAKING===
ShakingState::ShakingState(BagComponent* pBag)
	:BagState(pBag)
{
}

void ShakingState::Update(float deltaTime)
{
	m_ShakeTimer += deltaTime;
	UpdateVisuals();
	if(m_ShakeTimer >= m_ShakeTimerMax)
	{
		m_pBag->SetBagState(std::make_unique<FallingState>(m_pBag));
	}
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
	float jigglePeriod = 1.f / m_JigglesPerSec;
	int jiggleIndex = static_cast<int>(m_ShakeTimer / jigglePeriod) % 2;

	if (jiggleIndex == 0)
		m_pBag->SetTextureByRotation(BagRotation::LEFT);
	else
		m_pBag->SetTextureByRotation(BagRotation::RIGHT);
	//if (m_ShakeTimer > 1.5f) m_pBag->SetTextureByRotation(BagRotation::RIGHT);
	//else if (m_ShakeTimer > 1.f) m_pBag->SetTextureByRotation(BagRotation::NEUTRAL);
	//else if (m_ShakeTimer > 0.5f) m_pBag->SetTextureByRotation(BagRotation::LEFT);
	//else if (m_ShakeTimer > 0.f) m_pBag->SetTextureByRotation(BagRotation::NEUTRAL);
}

//===== FALLING ======
FallingState::FallingState(BagComponent* pBag)
	:BagState(pBag)
	, m_pOwnerTransform(nullptr)
{
	//is fine if only done once, but might aswell as falling happens once aswell
	dae::TransformComponent* ownerTransformPtr = m_pBag->GetGameObject()->GetComponent<dae::TransformComponent>();
	if (ownerTransformPtr) m_pOwnerTransform = ownerTransformPtr;
	else std::cout << "Bagstate transform is invalid for fallingState" << std::endl;
}

void FallingState::Update(float deltaTime)
{
	if(m_pOwnerTransform) m_pOwnerTransform->AddToLocalPosition(0.f, m_FallingSpeed * deltaTime);

}

void FallingState::OnEnter()
{
	//is fine if only done once, but might aswell as falling happens once aswell
	dae::TransformComponent* ownerTransformPtr = m_pBag->GetGameObject()->GetComponent<dae::TransformComponent>();
	if (ownerTransformPtr) m_pOwnerTransform = ownerTransformPtr;
	else std::cout << "Bagstate transform is invalid for fallingState" << std::endl;
}

void FallingState::OnExit()
{

}

BrokenState::BrokenState(BagComponent* pBag)
	:BagState(pBag)
	, m_pOwnerTransform(nullptr)
{
	dae::TransformComponent* ownerTransformPtr = m_pBag->GetGameObject()->GetComponent<dae::TransformComponent>();
	if (ownerTransformPtr) m_pOwnerTransform = ownerTransformPtr;
	else std::cout << "Bagstate transform is invalid for fallingState" << std::endl;
}

void BrokenState::Update(float)
{
}

void BrokenState::OnEnter()
{
}

void BrokenState::OnExit()
{
}


