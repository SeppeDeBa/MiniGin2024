#pragma once
#include <Command.h>

#include <glm/glm.hpp>
#include "GOCommand.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Level.h"

class GridMoveCommand final : public dae::GOCommand
{
public:
	GridMoveCommand(dae::GameObject* gameObjPtr, float speed, glm::vec2 moveVector);
	~GridMoveCommand();
	void Execute(float deltaTime) override;
	void SetSpeed(float speed);
	void SetNewTransform(dae::GameObject* gameObjPtr);
private:
	float m_Speed;
	glm::vec2 m_DirectionVector;
	dae::TransformComponent* m_pOwnerTransformComponent;
	const float m_GridCheckingOffset{0.05f};

	void ConsumeHorizontalInput(float deltaTime);
	void ConsumeVerticalInput(float deltaTime);

	bool WillCrossGridBorder(float deltaTime);
	const float m_GridMiddlePointY{ Level::s_tileHeight / 2.f };
	const float m_GridMiddlePointX{ Level::s_tileWidth / 2.f };
};
//class GridMoveCommand : public dae::Command
//{
//};

