#pragma once
#include "Component.h"
#include "TransformComponent.h"

enum class collisionTag
{
	Player,
	Bag,
	Enemy,
	Gem,
	Tile
};


class CollisionComponent : public dae::Component
{
public:
	CollisionComponent(dae::GameObject* pOwner, collisionTag tag, float radius, bool onlyReceivesCollision = false);
	virtual ~CollisionComponent() override;
	
	void Update(float deltaTime) override;
	virtual void InitOtherColliderTags() = 0;
	virtual void HandleCollision(collisionTag other) = 0;
	void CheckCollision(CollisionComponent* pOtherCollComponent);

	//getters
	bool GetReceivesOnly() const { return m_receiveOnly;};
	float GetCollisionRadius() const { return m_collisionRadius; };
	collisionTag GetCollisionTag() const { return m_collisionTag; };



private:
	const bool m_receiveOnly{};
	collisionTag m_collisionTag;
	const float m_collisionRadius{};
protected:
	dae::TransformComponent* m_pOwnersTransformComponent{};
	std::vector<collisionTag> m_CollidesWithTagsVec{};
};


