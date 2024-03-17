#pragma once
#include <glm/glm.hpp>
#include "GOCommand.h"
#include "SeppeUtils.h"
#include "GameObject.h"
#include "Transform.h"
namespace dae
{
	class MoveCommand final : public dae::GOCommand
	{
	public:
		MoveCommand(GameObject* gameObjPtr, float speed, glm::vec2 moveDirection);
		~MoveCommand();
		void Execute(float deltaTime) override;
		void SetSpeed(float speed);
	private:
		float m_Speed;
		glm::vec2 m_DirectionVector;
	};
};

