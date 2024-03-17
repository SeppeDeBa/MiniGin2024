#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class GOCommand : public Command
	{
	public:
		GOCommand(GameObject* gameObjPtr);
		virtual ~GOCommand();
		virtual void Execute(float deltaTime) = 0;
		GOCommand(const GOCommand& other) = delete;
		GOCommand(GOCommand&& other) = delete;
		GOCommand& operator=(const GOCommand& other) = delete;
		GOCommand& operator=(GOCommand&& other) = delete;

	protected:
		GameObject* m_pGameObject;
	};
}

