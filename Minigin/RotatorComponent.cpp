#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include <cmath>
//#define _USE_MATH_DEFINES
//#include <math.h>

dae::RotatorComponent::RotatorComponent(GameObject* pOwner, float radius, float rotationSpeedPerSec, bool goesClockwise, float startingRotation)
	: Component(pOwner)
	, m_circleRadius{ radius }
	, m_angle{ startingRotation }
	, m_rotationSpeedPerSec{ rotationSpeedPerSec }
	, m_goesClockwise{ goesClockwise }
{

}

dae::RotatorComponent::RotatorComponent(GameObject* pOwner, float radius, float rotationSpeedPerSec, bool goesClockwise)
	: Component(pOwner)
	, m_circleRadius{ radius }
	, m_angle{ 0.f }
	, m_rotationSpeedPerSec{ rotationSpeedPerSec }
	, m_goesClockwise{ goesClockwise }
{

}

dae::RotatorComponent::~RotatorComponent()
{
	if (m_pOwnerTransform != nullptr)
	{
		m_pOwnerTransform = nullptr;
	}
	if (m_pOwnerTextureComponent != nullptr)
	{
		m_pOwnerTextureComponent = nullptr;
		
	}
}

void dae::RotatorComponent::Update(float elapsedSec)
{
	//Calculate new angle
	if (m_goesClockwise)
	{
		m_angle -= m_rotationSpeedPerSec * elapsedSec;
	}
	else
	{
		m_angle += m_rotationSpeedPerSec * elapsedSec;//todo: take into account total rotation
	}

	//Check Both pointers to components of GameObject owner
	if (m_pOwnerTransform == nullptr)
	{
		m_pOwnerTransform = GetGameObject()->GetComponent<TransformComponent>();
	}
	if (m_pOwnerTextureComponent == nullptr)
	{
		m_pOwnerTextureComponent = GetGameObject()->GetComponent<TextureComponent>();
	}

	//Set rotation to the center of a textureComponent
	if (m_pOwnerTransform != nullptr && m_pOwnerTextureComponent != nullptr)
	{
		m_pOwnerTransform->SetLocalPosition(cos(m_angle * (float)M_PI / 180.f) * m_circleRadius /*+ (m_pOwnerTextureComponent->GetTextureSize().x/2.f)*/ //todo:does it need 2*m_pi?
										  , sin(m_angle * (float)M_PI / 180.f) * m_circleRadius /*+ (m_pOwnerTextureComponent->GetTextureSize().y / 2.f)*/);
		//todo: check std::number::pi
	}

	//Set rotation to the center of only a transformation
	else if (m_pOwnerTextureComponent != nullptr)
	{

	}

}
