#pragma once
#include <Command.h>

#include <glm/glm.hpp>
#include "GOCommand.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Player.h"
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
	Player* m_pOwnerPlayerComponent;
	const float m_GridCheckingOffset{0.05f};

	void ConsumeHorizontalInput(float deltaTime);
	void ConsumeVerticalInput(float deltaTime);

	void UpdatePlayerPosition(const playerDirection direction);
	void UpdatePlayerPositionHorizontal(float direction);
	void UpdatePlayerPositionVertical(float direction);

	bool WillCrossGridBorder(float deltaTime);
	const float m_GridMiddlePointY{ Grid::s_tileHeight / 2.f };
	const float m_GridMiddlePointX{ Grid::s_tileWidth / 2.f };
};
//class GridMoveCommand : public dae::Command
//{
//};

