#include "MapRegistryComponent.h"

MapRegistryComponent::MapRegistryComponent(dae::GameObject* pOwner, dae::GameObject* grid2Dptr, int rows, int cols)
	: Component(pOwner)
	, m_pGrid(grid2Dptr)
	, m_rowCount(rows)
	, m_colCount(cols)
{
	
}
