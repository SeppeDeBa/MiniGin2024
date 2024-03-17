#include "MoveCommand.h"

#include "TransformComponent.h"

dae::MoveCommand::MoveCommand(GameObject* gameObjPtr, float speed, glm::vec2 moveDirection)
	: GOCommand(gameObjPtr)
	, m_Speed{ speed }
	, m_DirectionVector(moveDirection)
{
}

dae::MoveCommand::~MoveCommand()
{
}

void dae::MoveCommand::Execute(float deltaTime)
{
	if(m_pGameObject)
	{
		m_pGameObject->GetComponent<dae::TransformComponent>()->AddToLocalPosition(
			m_DirectionVector.x * m_Speed * deltaTime, //x
			(m_DirectionVector.y * -1.f) * m_Speed * deltaTime); //y (inverted as y0 is top of screen)
	}
}

void dae::MoveCommand::SetSpeed(float speed)
{
	m_Speed = speed;
}


