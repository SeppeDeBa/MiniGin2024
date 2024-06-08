#pragma once
#include "CollisionComponent.h"

#include "Subject.h"
#include "ScoreTypeEnum.h"
#include "BagComponent.h"
class ScoreDisplayComponent;
class BagCollisionComponent : public CollisionComponent
{
public:
	BagCollisionComponent(dae::GameObject* pOwner, ScoreDisplayComponent* mainScorePtr);
	~BagCollisionComponent() override = default;
	void InitOtherColliderTags() override;
	void HandleCollision(collisionTag other, glm::vec3 otherWorldLoc) override;

private:
	BagComponent* m_pBag{};
	Subject<ScoreType> m_scoreSubject{};
};

