#include "CollisionManager.h"

void CollisionManager::ClearCollisionVec()
{
	m_pActiveCollisions.clear();//non destructive clearing (not owners)
}

void CollisionManager::AddCollisionComp(CollisionComponent* pCollisionToAdd)
{
	m_pActiveCollisions.push_back(pCollisionToAdd);
}

void CollisionManager::RemoveCollisionComp(CollisionComponent* pCollisionToRemove)
{
	auto i = std::find(m_pActiveCollisions.begin(), m_pActiveCollisions.end(), pCollisionToRemove);
		if (i != m_pActiveCollisions.end())
		{
			m_pActiveCollisions.erase(i);
		}
}


const std::vector<CollisionComponent*>& CollisionManager::GetCollisions() const
{
	return m_pActiveCollisions;
}

