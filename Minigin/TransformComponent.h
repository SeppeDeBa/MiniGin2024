#pragma once
#include "Component.h"
namespace dae
{

	class TransformComponent : public Component
	{
	public:
		TransformComponent(GameObject* pOwner, float x, float y);
		~TransformComponent();
		void Update(float deltaTime) override;


		void SetPosition(float x, float y);
		void AddPosition(float x, float y);
		glm::vec3 getPosition();

	private:
		glm::vec3 m_position{};//might aswell do vec3
	};
}
