#include "BagComponent.h"
#include "BagState.h"
#include "ResourceManager.h"
#include "TextureComponent.h"

BagComponent::BagComponent(dae::GameObject* pOwner)
	:dae::Component(pOwner)
	, m_pBagState(std::make_unique<ShakingState>(this))
{
	InitBagTextures();
}

void BagComponent::SetTextureByRotation(const BagRotation rotation)
{
	GetGameObject()->GetComponent<dae::TextureComponent>()->SetTexture(m_pTexturesMap[rotation]);
}

void BagComponent::Update(float deltaT)
{
	m_pBagState->Update(deltaT);
}

void BagComponent::Render() const
{
	
}

void BagComponent::FixedUpdate()
{
	
}

void BagComponent::SetBagState(std::unique_ptr<BagState> pBagStateToSet)
{
	m_pBagState->OnExit();
	m_pBagState = std::move(pBagStateToSet);
	m_pBagState->OnEnter();
}

void BagComponent::InitBagTextures()
{
	std::string bagString{ "Bag" };

	//different textures
	std::string leftRotationFP{ bagString + "L.png" };
	std::string rightRotationFP{ bagString + "R.png" };
	std::string neutralRotationFP{ bagString + ".png" };
	//assigning

	//left
	m_pTexturesMap.insert({ BagRotation::LEFT,
			dae::ResourceManager::GetInstance().LoadTexture(leftRotationFP) });
	//middle
	m_pTexturesMap.insert({ BagRotation::RIGHT,
		dae::ResourceManager::GetInstance().LoadTexture(rightRotationFP) });
	//right
	m_pTexturesMap.insert({ BagRotation::NEUTRAL,
	dae::ResourceManager::GetInstance().LoadTexture(neutralRotationFP) });

}

//===== FALLINGSTATE =====

