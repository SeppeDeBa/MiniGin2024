#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* pOwner, float x, float y)
	: Component(pOwner)
	,m_position(x, y, 0.f)
{

}


void dae::TransformComponent::Update(float)
{

}

void dae::TransformComponent::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void dae::TransformComponent::AddPosition(float x, float y)
{
	m_position.x += x;
	m_position.y += y;

}

glm::vec3 dae::TransformComponent::GetPosition() const
{
	return m_position;
}

