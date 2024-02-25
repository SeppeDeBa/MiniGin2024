#pragma once
#include <glm/glm.hpp>

#include "Component.h"
namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* pOwner, float x, float y);
		~TransformComponent() override = default;
		void Update(float deltaTime) override;


		void SetPosition(float x, float y);
		void AddPosition(float x, float y);
		glm::vec3 GetPosition() const;

	private:
		glm::vec3 m_position{};//might aswell do vec3
	};
}
