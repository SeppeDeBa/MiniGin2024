#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* pOwner, float x, float y)
	: Component(pOwner)
	,m_position(x, y, 0.f)
{

}

dae::TransformComponent::~TransformComponent()
{
}

void dae::TransformComponent::Update(float deltaTime)
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

glm::vec3 dae::TransformComponent::getPosition()
{
	return m_position;
}

