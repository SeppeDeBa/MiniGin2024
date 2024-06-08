#pragma once
#include "CollisionComponent.h"

#include "Subject.h"
#include "ScoreTypeEnum.h"

class ScoreDisplayComponent;
class GemCollisionComponent : public CollisionComponent
{
public:
	GemCollisionComponent(dae::GameObject* pOwner, ScoreDisplayComponent* mainScorePtr);
	~GemCollisionComponent() override = default;
	void InitOtherColliderTags() override;
	void HandleCollision(collisionTag other, glm::vec3) override;

private:
	Subject<ScoreType> m_scoreSubject{};
};

