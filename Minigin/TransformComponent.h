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


		//local pos
		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec3& vecInput);
		void AddToLocalPosition(float x, float y);
		void AddToLocalPosition(float x, float y, float z);
		const glm::vec3& GetLocalPos() const { return m_localPos; };


		//world pos
		void UpdateWorldPos();
		glm::vec3 GetWorldPos();


		//dirty flag
		void SetTransformDirty() { m_positionIsDirty = true; };

		//void SetPosition(float x, float y);
		//void AddPosition(float x, float y);
		//glm::vec3 GetPosition() const;

	private:
		//glm::vec3 m_position{};//might aswell do vec3
		glm::vec3 m_localPos{};
		glm::vec3 m_worldPos{};
		bool m_positionIsDirty{ true };
	};
}
