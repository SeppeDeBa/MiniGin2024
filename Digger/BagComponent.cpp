#include "BagComponent.h"

#include "ResourceManager.h"
#include "TextureComponent.h"

BagComponent::BagComponent(dae::GameObject* pOwner)
	:dae::Component(pOwner)
{
	InitBagTextures();
}

void BagComponent::SetTextureByRotation(const BagRotation rotation)
{
	GetGameObject()->GetComponent<dae::TextureComponent>()->SetTexture(m_pTexturesMap[rotation]);
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
