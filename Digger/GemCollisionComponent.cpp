#include "GemCollisionComponent.h"
#include "ScoreDisplayComponent.h"
GemCollisionComponent::GemCollisionComponent(dae::GameObject* pOwner, ScoreDisplayComponent* mainScorePtr)
	:CollisionComponent(pOwner, collisionTag::Gem, 12.f, true)

{
	m_scoreSubject.AddObserver(mainScorePtr);
}

void GemCollisionComponent::InitOtherColliderTags()
{
	//blank
}

void GemCollisionComponent::HandleCollision(collisionTag other, glm::vec3)
{
	if(other == collisionTag::Player)
	{
		m_scoreSubject.Notify(ScoreType::EMERALDS);
		GetGameObject()->MarkForDeletion();
	}
}
