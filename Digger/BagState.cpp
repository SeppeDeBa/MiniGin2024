#include "BagState.h"
#include "BagComponent.h"
#include <iostream>

#include "Grid.h"

//Base
BagState::BagState(BagComponent* pBag)
	:m_pBag(pBag)
	,m_pOwnerTransform(nullptr)
	,m_pMap(nullptr)
{
	//dae::TransformComponent* ownerTransformPtr = m_pBag->GetGameObject()->GetComponent<dae::TransformComponent>();
	if (dae::TransformComponent* ownerTransformPtr = m_pBag->GetGameObject()->GetComponent<dae::TransformComponent>())
		m_pOwnerTransform = ownerTransformPtr;
	else std::cout << "Bagstate transform is invalid for fallingState" << std::endl;


	//MapRegistryComponent* ownerMapPtr = m_pBag->GetGameObject()->GetComponent<MapRegistryComponent>();
	if (MapRegistryComponent* ownerMapPtr = m_pBag->GetGameObject()->GetComponent<MapRegistryComponent>())
		m_pMap = ownerMapPtr;
	else std::cout << "Bagstate transform is invalid for fallingState" << std::endl;
}

bool BagState::tileUnderneathIsClosed() const
{
	if(m_pOwnerTransform)
	{
		//calculate pos on tile underneath
		glm::vec3 bagTransform = m_pOwnerTransform->GetWorldPos();
		bagTransform.y += Grid::s_tileHeight;

		if (!Grid::pointIsInGrid({ bagTransform.x, bagTransform.y }))	return true;  //say tile is closed when last grid
		else if(m_pMap->GetGrid()->IsTileOpenFromWorldPos(bagTransform.x, bagTransform.y))
		{
			return false;
		}
	}
	return true; //errors are logged on creation
}

//===NEUTRAL===
NeutralState::NeutralState(BagComponent* pBag)
	:BagState(pBag)
{
	if (m_pOwnerTransform)
	{
		glm::vec3 bagLoc = m_pOwnerTransform->GetWorldPos();
		m_pBag->lastStableRow = static_cast<int>(Grid::GetLevelTilePosition(bagLoc.x, bagLoc.y).y);
	}
}

void NeutralState::Update(float)
{
	
}

void NeutralState::FixedUpdate()
{
	if (!tileUnderneathIsClosed()) m_pBag->SetBagState(std::make_unique<ShakingState>(m_pBag));
}

void NeutralState::OnEnter()
{

}

void NeutralState::OnExit()
{
	std::cout << "bag starts falling" << std::endl;
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

void ShakingState::FixedUpdate()
{
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
{
	//dae::TransformComponent* ownerTransformPtr = m_pBag->GetGameObject()->GetComponent<dae::TransformComponent>();
	if (dae::TransformComponent* ownerTransformPtr = m_pBag->GetGameObject()->GetComponent<dae::TransformComponent>()) 
		m_pOwnerTransform = ownerTransformPtr;
	else std::cout << "Bagstate transform is invalid for fallingState" << std::endl;


	//MapRegistryComponent* ownerMapPtr = m_pBag->GetGameObject()->GetComponent<MapRegistryComponent>();
	if (MapRegistryComponent* ownerMapPtr = m_pBag->GetGameObject()->GetComponent<MapRegistryComponent>())
		m_pMap = ownerMapPtr;
	else std::cout << "Bagstate transform is invalid for fallingState" << std::endl;
}

void FallingState::Update(float deltaTime)
{
	if(m_pOwnerTransform) m_pOwnerTransform->AddToLocalPosition(0.f, m_FallingSpeed * deltaTime);


}

void FallingState::FixedUpdate()
{
	bool halfwayTile{ false };
	


	if (tileUnderneathIsClosed())
	{
		float yPos = m_pOwnerTransform->GetWorldPos().y;
		float tileHeight = Grid::s_tileHeight;
		halfwayTile = (static_cast<int>(yPos) % static_cast<int>(tileHeight)) >= (tileHeight / 2 + m_DistanceToGroundExtra);

		if (halfwayTile) //change to new state
		{
			if (m_pOwnerTransform)
			{
				glm::vec3 bagLoc = m_pOwnerTransform->GetWorldPos();
				int currentRow = static_cast<int>(Grid::GetLevelTilePosition(bagLoc.x, bagLoc.y).y);

				if(currentRow >= m_pBag->lastStableRow + m_TilesFallenToBreak) m_pBag->SetBagState(std::make_unique<BrokenState>(m_pBag));
				else m_pBag->SetBagState(std::make_unique<NeutralState>(m_pBag));
			}
		}
	}
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
{

}

void BrokenState::Update(float)
{
}

void BrokenState::FixedUpdate()
{
}

void BrokenState::OnEnter()
{
	m_pBag->SetTextureByRotation(BagRotation::OPEN);
}

void BrokenState::OnExit()
{
}


