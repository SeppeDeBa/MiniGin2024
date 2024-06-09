#include "PlayerCollisionComponent.h"
#include "LivesDisplayComponent.h"
PlayerCollisionComponent::PlayerCollisionComponent(dae::GameObject* pOwner, LivesDisplayComponent* mainLivesPtr)
	:CollisionComponent(pOwner, collisionTag::Player, 16.f, false)
{
	InitOtherColliderTags();

	m_playerDiesSubject.AddObserver(mainLivesPtr);
}

void PlayerCollisionComponent::InitOtherColliderTags()
{
	m_CollidesWithTagsVec.push_back(collisionTag::Gem);
	m_CollidesWithTagsVec.push_back(collisionTag::Enemy);
	m_CollidesWithTagsVec.push_back(collisionTag::Bag);
}

void PlayerCollisionComponent::HandleCollision(collisionTag other, glm::vec3)
{
	if(other == collisionTag::Enemy)
	{
		//m_playerDiesSubject.Notify(1);//todo: fix bug here, according to error 0xFFFFFFFFFFFFFFD7. its usually some vector or container, changing in size and possibly invalidating pointers to it.
	}

}
