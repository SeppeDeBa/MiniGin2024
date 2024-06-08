#include "PlayerCollisionComponent.h"

PlayerCollisionComponent::PlayerCollisionComponent(dae::GameObject* pOwner)
	:CollisionComponent(pOwner, collisionTag::Player, 16.f, false)
{
	InitOtherColliderTags();
}

void PlayerCollisionComponent::InitOtherColliderTags()
{
	m_CollidesWithTagsVec.push_back(collisionTag::Gem);
	m_CollidesWithTagsVec.push_back(collisionTag::Enemy);
	m_CollidesWithTagsVec.push_back(collisionTag::Bag);
}

void PlayerCollisionComponent::HandleCollision(collisionTag, glm::vec3)
{
	//todo: damaged when touching enemy
}
