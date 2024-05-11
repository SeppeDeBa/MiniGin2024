#include "CollisionComponent.h"

dae::CollisionComponent::CollisionComponent(GameObject* pOwner, collisionTag tag, bool onlyReceivesCollision)
	:Component(pOwner)
	,m_receiveOnly{onlyReceivesCollision}
	,m_collisionTag{tag}
{
	if (GetGameObject()->HasComponent<TransformComponent>())
	{
		m_pOwnersTransformComponent = GetGameObject()->GetComponent<TransformComponent>();
	}
}

dae::CollisionComponent::~CollisionComponent()
{
}

void dae::CollisionComponent::Update(float deltaTime)
{
}

void dae::CollisionComponent::HandleCollision(collisionTag other)
{
}
