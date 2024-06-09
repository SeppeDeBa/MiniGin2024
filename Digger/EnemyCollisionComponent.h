#pragma once
#include "CollisionComponent.h"

#include "Subject.h"
#include "ScoreTypeEnum.h"
class ScoreDisplayComponent;

class EnemyCollisionComponent : public CollisionComponent
{
public:
	EnemyCollisionComponent(dae::GameObject* pOwner, ScoreDisplayComponent* mainScorePtr);
	~EnemyCollisionComponent() override = default;
	void InitOtherColliderTags() override;
	void HandleCollision(collisionTag other, glm::vec3) override;

private:
	Subject<ScoreType> m_scoreSubject{};
};

