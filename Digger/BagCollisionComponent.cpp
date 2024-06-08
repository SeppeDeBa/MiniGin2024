 #include "BagCollisionComponent.h"

#include "Grid.h"
#include "ScoreDisplayComponent.h"

 BagCollisionComponent::BagCollisionComponent(dae::GameObject* pOwner, ScoreDisplayComponent* mainScorePtr)
	 :CollisionComponent(pOwner, collisionTag::Bag, 16.f, true)
{
 	BagComponent* ownerBagComp = pOwner->GetComponent<BagComponent>();
	if (ownerBagComp) m_pBag = ownerBagComp;
	else std::cout << "BagComp not initialized yet in a bagCollisionComp" << std::endl;


	m_scoreSubject.AddObserver(mainScorePtr);
}

 void BagCollisionComponent::InitOtherColliderTags()
 {
	 //blank
 }

 void BagCollisionComponent::HandleCollision(collisionTag other, glm::vec3 otherWorldLoc)//todo: think about cleaning up nesting if statements
 {
	 if(other == collisionTag::Player && m_pBag->CanCollect())
	 {
		 m_scoreSubject.Notify(ScoreType::EMERALDS);
		 GetGameObject()->MarkForDeletion();
	 }
	 else if(other == collisionTag::Player && m_pBag->CanPush())
	 {
	 	bool otherActorIsLeft{ GetOwnerWorldLoc().x > otherWorldLoc.x }; //seperate initialization for visual clarity, personal choice
	 	glm::vec2 locToPushTo{ m_pOwnersTransformComponent->GetWorldPos().x, m_pOwnersTransformComponent->GetWorldPos().y};//initializing to add offset to
	 	if (otherActorIsLeft)
		{
			locToPushTo.x += Grid::s_tileWidth;
			if (Grid::pointIsInGrid(locToPushTo)) 
				m_pOwnersTransformComponent->AddToLocalPosition(Grid::s_tileWidth, 0.f);
		}
		else
		{
			locToPushTo.x -= Grid::s_tileWidth;
			if (Grid::pointIsInGrid(locToPushTo)) 
				m_pOwnersTransformComponent->AddToLocalPosition(-Grid::s_tileWidth, 0.f);
		}
	 }
 }
