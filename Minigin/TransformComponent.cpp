#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* pOwner, float x, float y)
	: Component(pOwner)
	,m_localPos(x, y, 0.f)
{

}


void dae::TransformComponent::Update(float)
{
	UpdateWorldPos();
}

void dae::TransformComponent::SetLocalPosition(float x, float y, float z)
{
	m_localPos.x = x;
	m_localPos.y = y;
	m_localPos.z = z;
	GetGameObject()->SetPositionDirty();//todo: ask if this is necessary? upwards dirty setting? is it ever needed?
}

void dae::TransformComponent::SetLocalPosition(float x, float y)
{
	m_localPos.x = x;
	m_localPos.y = y;
	GetGameObject()->SetPositionDirty();
}

void dae::TransformComponent::SetLocalPosition(const glm::vec3& vecInput)
{
	m_localPos = vecInput;
	GetGameObject()->SetPositionDirty();
}

void dae::TransformComponent::AddToLocalPosition(float x, float y)
{
	m_localPos.x += x;
	m_localPos.y += y;
	GetGameObject()->SetPositionDirty();
}

void dae::TransformComponent::AddToLocalPosition(float x, float y, float z)
{
	m_localPos.x += x;
	m_localPos.y += y;
	m_localPos.z += z;
	GetGameObject()->SetPositionDirty();
}

void dae::TransformComponent::UpdateWorldPos()
{
	if (m_positionIsDirty)
	{
		if (GetGameObject()->GetParent() == nullptr)
		{
			m_worldPos = m_localPos;
		}
		else
		{
			m_worldPos = GetGameObject()->GetParent()->GetComponent<TransformComponent>()->GetWorldPos() + m_localPos;
			//need to optimise this by saving some of this data in members! such as: Parent or Parent Transform even.
		}
		m_positionIsDirty = false;
	}
}

glm::vec3 dae::TransformComponent::GetWorldPos()
{
	if (m_positionIsDirty) UpdateWorldPos();
	return m_worldPos;

}


//void dae::TransformComponent::SetPosition(float x, float y)
//{
//	m_position.x = x;
//	m_position.y = y;
//}
//
//void dae::TransformComponent::AddPosition(float x, float y)
//{
//	m_position.x += x;
//	m_position.y += y;
//
//}
//
//glm::vec3 dae::TransformComponent::GetPosition() const
//{
//	return m_position;
//}

