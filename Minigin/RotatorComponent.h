#pragma once
#include "Component.h"
#include <glm/glm.hpp>
namespace dae
{
	class TransformComponent;
	class TextureComponent;
	class RotatorComponent : public Component
	{
	public:
		RotatorComponent(GameObject* pOwner, float radius, float rotationSpeedPerSec, bool goesClockwise, float startingRotation);
		RotatorComponent(GameObject* pOwner, float radius, float rotationSpeedPerSec, bool goesClockwise);
		~RotatorComponent() override;


		void Update(float elapsedSec) override;

	private:

		float m_circleRadius;
		float m_angle;
		float m_rotationSpeedPerSec;
		bool m_goesClockwise; //todo: change to float
		TransformComponent* m_pOwnerTransform{};
		TextureComponent* m_pOwnerTextureComponent{};
	};
}


