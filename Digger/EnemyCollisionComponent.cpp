#include "EnemyCollisionComponent.h"
#include "ScoreDisplayComponent.h"
#include "GameObject.h"
#include "EnemyComponent.h"
EnemyCollisionComponent::EnemyCollisionComponent(dae::GameObject* pOwner, ScoreDisplayComponent* mainScorePtr)
:CollisionComponent(pOwner, collisionTag::Enemy, 16.f, true)
{
	m_scoreSubject.AddObserver(mainScorePtr);
}

void EnemyCollisionComponent::InitOtherColliderTags()
{
	m_CollidesWithTagsVec.push_back(collisionTag::Bag);
}

void EnemyCollisionComponent::HandleCollision(collisionTag other, glm::vec3)
{
	if(other == collisionTag::Bag)
	{
		EnemyComponent* parentEnemyCompPtr = GetGameObject()->GetComponent<EnemyComponent>();

		if(parentEnemyCompPtr->GetIsTransformed())
		{
			m_scoreSubject.Notify(ScoreType::HOBBINS);
		}
		else
		{
			m_scoreSubject.Notify(ScoreType::NOBBINS);
		}
		GetGameObject()->MarkForDeletion();
	}
}
