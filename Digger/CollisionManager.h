#pragma once
#include "TransformComponent.h"
#include <Singleton.h>

#include "CollisionComponent.h"

class CollisionManager final: public dae::Singleton<CollisionManager>	
{
public:
	CollisionManager() = default;
	~CollisionManager() override = default;
	void ClearCollisionVec();
	void AddCollisionComp(CollisionComponent* pCollisionToAdd);
	void RemoveCollisionComp(CollisionComponent* pCollisionToRemove);
	const std::vector<CollisionComponent*>& GetCollisions() const;
private:
	std::vector<CollisionComponent*> m_pActiveCollisions;




};

