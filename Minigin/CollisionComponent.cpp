#include "CollisionComponent.h"

dae::CollisionComponent::CollisionComponent(GameObject* pOwner, collisionTag tag, float radius, bool onlyReceivesCollision)
	:Component(pOwner)
	,m_receiveOnly{onlyReceivesCollision}
	,m_collisionTag{tag}
	,m_collisionRadius(radius)
{
	if (GetGameObject()->HasComponent<TransformComponent>())
	{
		m_pOwnersTransformComponent = GetGameObject()->GetComponent<TransformComponent>();
	}
}

dae::CollisionComponent::~CollisionComponent()
{

}

void dae::CollisionComponent::Update(float)
{

}


void dae::CollisionComponent::CheckCollision(CollisionComponent* pOtherCollComponent)
{
	if (!m_receiveOnly)
	{
		glm::vec3 otherActorLocation = pOtherCollComponent->m_pOwnersTransformComponent->GetWorldPos();
		const float distToOtherActorX = abs(m_pOwnersTransformComponent->GetWorldPos().x - otherActorLocation.x);
		const float distToOtherActorY = abs(m_pOwnersTransformComponent->GetWorldPos().y - otherActorLocation.y);
		if (distToOtherActorX <= m_collisionRadius
			&& distToOtherActorY <= m_collisionRadius)
		{
			HandleCollision(pOtherCollComponent->m_collisionTag);
			pOtherCollComponent->HandleCollision(m_collisionTag);
		}
	}
}
