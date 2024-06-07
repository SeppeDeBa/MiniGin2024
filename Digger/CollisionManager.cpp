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
    auto it = std::find(m_pActiveCollisions.begin(), m_pActiveCollisions.end(), pCollisionToRemove);
    if (it != m_pActiveCollisions.end())
    {
        m_pActiveCollisions.erase(it);
    }
}


const std::vector<CollisionComponent*>& CollisionManager::GetCollisions() const
{
	return m_pActiveCollisions;
}

