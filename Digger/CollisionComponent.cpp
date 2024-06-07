#include "CollisionComponent.h"

#include <iostream>
#include <algorithm>
#include "CollisionManager.h"

CollisionComponent::CollisionComponent(dae::GameObject* pOwner, collisionTag tag, float radius, bool onlyReceivesCollision)
	:Component(pOwner)
	,m_receiveOnly{onlyReceivesCollision}
	,m_collisionTag{tag}
	,m_collisionRadius(radius)
{
	if (GetGameObject()->HasComponent<dae::TransformComponent>())
	{
		m_pOwnersTransformComponent = GetGameObject()->GetComponent<dae::TransformComponent>();
	}
	else
	{
		std::cout << "A collisionComponent doesnt have an object with tag:" << std::to_string(static_cast<int>(tag)) << std::endl;
	}
	CollisionManager::GetInstance().AddCollisionComp(this);
}

CollisionComponent::~CollisionComponent()
{
	CollisionManager::GetInstance().RemoveCollisionComp(this);
}

void CollisionComponent::Update(float)
{

}




void CollisionComponent::CheckCollision(CollisionComponent* pOtherCollComponent)
{
	if (!m_receiveOnly && 
		std::find(m_CollidesWithTagsVec.begin(), m_CollidesWithTagsVec.end(), pOtherCollComponent->GetCollisionTag()) != m_CollidesWithTagsVec.end())
	{
		glm::vec3 otherActorLocation = pOtherCollComponent->m_pOwnersTransformComponent->GetWorldPos();
		const float distToOtherActorX = abs(m_pOwnersTransformComponent->GetWorldPos().x - otherActorLocation.x);
		const float distToOtherActorY = abs(m_pOwnersTransformComponent->GetWorldPos().y - otherActorLocation.y);
		if (distToOtherActorX <= (m_collisionRadius + pOtherCollComponent->m_collisionRadius)
			&& distToOtherActorY <= (m_collisionRadius + pOtherCollComponent->m_collisionRadius))
		{
			HandleCollision(pOtherCollComponent->m_collisionTag);
			pOtherCollComponent->HandleCollision(m_collisionTag);
		}
	}
}
