#include "GridMoveCommand.h"

GridMoveCommand::GridMoveCommand(dae::GameObject* gameObjPtr, float speed, glm::vec2 moveVector)
	: dae::GOCommand(gameObjPtr)
	, m_Speed(speed)
	, m_DirectionVector(moveVector)
	, m_pOwnerTransformComponent(gameObjPtr->GetComponent<dae::TransformComponent>())
{
}

GridMoveCommand::~GridMoveCommand()
{
}

void GridMoveCommand::Execute(float deltaTime)
{
	if(m_pOwnerTransformComponent && !WillCrossGridBorder(deltaTime))
	{
		if(m_DirectionVector.x != 0)
		{
			ConsumeHorizontalInput(deltaTime);
		}
		if(m_DirectionVector.y != 0)
		{
			ConsumeVerticalInput(deltaTime);
		}
	}
}

void GridMoveCommand::SetSpeed(float speed)
{
	m_Speed = speed;
}

void GridMoveCommand::SetNewTransform(dae::GameObject* gameObjPtr)
{
	m_pOwnerTransformComponent = gameObjPtr->GetComponent<dae::TransformComponent>();
}

void GridMoveCommand::ConsumeHorizontalInput(float deltaTime)
{
	float gridYPos{ m_pOwnerTransformComponent->GetWorldPos().y / Level::s_tileHeight }; 
	float gridRow{};
	float gridRowRelativeYPos = modf(gridYPos, &gridRow);


	//check if the YPos is within bounds
	if(gridRowRelativeYPos > (0.5f - m_GridCheckingOffset)
	&& gridRowRelativeYPos < (0.5f + m_GridCheckingOffset)	) // movement is on grid so do what must be done
	{
		m_pOwnerTransformComponent->AddToLocalPosition(m_DirectionVector.x * m_Speed * deltaTime, 0.f);
	}
	else if (gridRowRelativeYPos <= 0.5f)//position is not on the grid to move over X, move to Y center
	{
		m_pOwnerTransformComponent->AddToLocalPosition(0.f, m_Speed * deltaTime);
	}
	else
	{
		m_pOwnerTransformComponent->AddToLocalPosition(0.f, -m_Speed * deltaTime);
	}
}

void GridMoveCommand::ConsumeVerticalInput(float deltaTime)
{
	float gridXPos{ m_pOwnerTransformComponent->GetWorldPos().x / Level::s_tileWidth };
	float gridCol{};
	float gridColRelativeXPos = modf(gridXPos, &gridCol);


	//check if the YPos is within bounds
	if (gridColRelativeXPos > (0.5f - m_GridCheckingOffset)
		&& gridColRelativeXPos < (0.5f + m_GridCheckingOffset)) // movement is on grid so do what must be done
	{
		m_pOwnerTransformComponent->AddToLocalPosition(0.f, -1.f * m_DirectionVector.y * m_Speed * deltaTime);
	}
	else if (gridColRelativeXPos <= 0.5f)//position is not on the grid to move over X, move to Y center
	{
		m_pOwnerTransformComponent->AddToLocalPosition(m_Speed * deltaTime, 0.f);
	}
	else
	{
		m_pOwnerTransformComponent->AddToLocalPosition(-m_Speed * deltaTime, 0.f);
	}
}

bool GridMoveCommand::WillCrossGridBorder(float deltaTime)
{
	if(m_pOwnerTransformComponent)
	{
		glm::vec2 pointToCheck{ m_DirectionVector * m_Speed * deltaTime};
		pointToCheck.y *= -1;
		pointToCheck.x += m_pOwnerTransformComponent->GetWorldPos().x;
		pointToCheck.y += m_pOwnerTransformComponent->GetWorldPos().y;
		return !Level::pointIsInGrid(pointToCheck);
	}
	std::cout << "m_pOwnerTransformComponent is invalid in WilLCrossGridBroder" << std::endl;
	return false;
}