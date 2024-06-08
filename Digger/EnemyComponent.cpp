#include "EnemyComponent.h"
#include <algorithm>
#include "GridMoveCommand.h"
#include "MapRegistryComponent.h"
#include "Grid.h"

EnemyComponent::EnemyComponent(dae::GameObject* pOwner, bool startsAsHobbin)
	:dae::Component(pOwner)
{
	dae::TransformComponent* pOwnerTransform = pOwner->GetComponent<dae::TransformComponent>();
	if (pOwnerTransform) m_pOwnerTransform = pOwnerTransform;
	else std::cout << "a transform is not initialized for an enemy" << std::endl;

	MapRegistryComponent* pRegister = pOwner->GetComponent<MapRegistryComponent>();
	if (pRegister) m_pMapRegister = pRegister;
	else std::cout << "No map register linked to an enemy" << std::endl;

	m_InitTextures();
	m_InitCommands();
	if (startsAsHobbin) m_Transform();
}

void EnemyComponent::Update(float deltaTime)
{
	if(!m_IsTransformed)
	{
		m_TransformTimerCurrent += deltaTime;
		if (m_TransformTimerCurrent > m_TransformTimerMax) m_Transform();
	}


	m_moveCommandsMap[m_DirectionGoing]->Execute(deltaTime);
}

void EnemyComponent::FixedUpdate()
{
	if (m_DirectionGoing == facingDirection::ENEMYUP) std::cout << "MOVING UP" << std::endl;
	if (m_DirectionGoing == facingDirection::ENEMYRIGHT) std::cout << "MOVING RIGHT" << std::endl;
	if (m_pOwnerTransform)
	{
		glm::vec2 currentGridPos = Grid::GetLevelTilePosition(m_pOwnerTransform->GetWorldPos().x,
										m_pOwnerTransform->GetWorldPos().y);
		if(m_lastGridPos != currentGridPos)
		{
			m_UpdateFacingDirection();
			m_lastGridPos = currentGridPos;
		}
	}
}


void EnemyComponent::m_Transform()
{
	m_IsTransformed = true;
	GetGameObject()->GetComponent<dae::TextureComponent>()->SetTexture(m_pHobbinTexture);
	//speed up! zooom
	for (auto& [key, value] : m_moveCommandsMap)
	{
		value->SetSpeed(m_HobbinsMoveSpeed);
	}
}

void EnemyComponent::m_SetDirection(facingDirection toSet)
{
	m_DirectionCameFrom = m_GetOppositeDirection(m_DirectionGoing);
	m_DirectionGoing = toSet;
}

facingDirection EnemyComponent::m_GetOppositeDirection(facingDirection input)
{
	switch(input)
	{
	case ENEMYLEFT:
		return ENEMYRIGHT;
		break;

	case ENEMYDOWN:
		return ENEMYUP;
		break;

	case ENEMYRIGHT:
		return ENEMYLEFT;
		break;

	case ENEMYUP:
		return ENEMYDOWN;
		break;

	default:
		return ENEMYUP;
	}
}

bool EnemyComponent::m_NavigationCheck(float x, float y) const //checks if the location can be moved to by enemy
{
	if (!Grid::pointIsInGrid({ x,y })) return false;

	//glm::vec2 gridPos{ Grid::GetLevelTilePosition(x,y) };
	return m_pMapRegister->GetGrid()->IsTileOpenFromWorldPos(x, y);
}

void EnemyComponent::m_UpdateFacingDirection()
{
	//create empty vector and get location
	std::vector<facingDirection> availableDirections{};
	glm::vec3 ownerPos = m_pOwnerTransform->GetWorldPos();
	//check all directions
	//up & down
	if (m_DirectionCameFrom!=ENEMYUP && m_NavigationCheck(ownerPos.x, ownerPos.y - Grid::s_tileHeight))
		availableDirections.push_back(facingDirection::ENEMYUP);
	if (m_DirectionCameFrom != ENEMYDOWN && m_NavigationCheck(ownerPos.x, ownerPos.y + Grid::s_tileHeight))
		availableDirections.push_back(facingDirection::ENEMYDOWN);
	//left & right
	if (m_DirectionCameFrom != ENEMYLEFT && m_NavigationCheck(ownerPos.x - Grid::s_tileWidth, ownerPos.y))
		availableDirections.push_back(facingDirection::ENEMYLEFT);
	if (m_DirectionCameFrom != ENEMYRIGHT && m_NavigationCheck(ownerPos.x + Grid::s_tileWidth, ownerPos.y))
		availableDirections.push_back(facingDirection::ENEMYRIGHT);

	//none found = move back where it came from
	if(availableDirections.empty()) 
	{
		m_DirectionGoing = m_DirectionCameFrom;
		m_DirectionCameFrom = m_GetOppositeDirection(m_DirectionGoing);
	}
	//else take random direction
	else
	{
		std::shuffle(availableDirections.begin(), availableDirections.end(), m_randomDevice);
		m_SetDirection(availableDirections.front());//pick first as its shuffled
	}


}

void EnemyComponent::m_InitTextures()
{
	m_pHobbinTexture = dae::ResourceManager::GetInstance().LoadTexture("Hobbin.png");
	m_pNobbinTexture = dae::ResourceManager::GetInstance().LoadTexture("Nobbin.png");
}

void EnemyComponent::m_InitCommands()
{
	glm::vec2 left{ -1.f, 0.f };
	glm::vec2 right{ 1.f, 0.f };
	glm::vec2 up{ 0.f, 1.f };
	glm::vec2 down{ 0.f, -1.f };
	std::unique_ptr<GridMoveCommand> pMoveLeft = std::make_unique<GridMoveCommand>(GetGameObject(), m_NobbinsMoveSpeed, left);
	std::unique_ptr<GridMoveCommand> pMoveRight = std::make_unique<GridMoveCommand>(GetGameObject(), m_NobbinsMoveSpeed, right);
	std::unique_ptr<GridMoveCommand> pMoveUp = std::make_unique<GridMoveCommand>(GetGameObject(), m_NobbinsMoveSpeed, up);
	std::unique_ptr<GridMoveCommand> pMoveDown = std::make_unique<GridMoveCommand>(GetGameObject(), m_NobbinsMoveSpeed, down);

	m_moveCommandsMap.insert(std::pair<facingDirection, std::unique_ptr<GridMoveCommand>>{ facingDirection::ENEMYLEFT, std::move(pMoveLeft) });
	m_moveCommandsMap.insert(std::pair<facingDirection, std::unique_ptr<GridMoveCommand>>{ facingDirection::ENEMYRIGHT, std::move(pMoveRight) });
	m_moveCommandsMap.insert(std::pair<facingDirection, std::unique_ptr<GridMoveCommand>>{ facingDirection::ENEMYUP, std::move(pMoveUp) });
	m_moveCommandsMap.insert(std::pair<facingDirection, std::unique_ptr<GridMoveCommand>>{ facingDirection::ENEMYDOWN, std::move(pMoveDown) });
}
