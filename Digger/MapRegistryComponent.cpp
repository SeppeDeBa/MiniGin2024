#include "MapRegistryComponent.h"
#include "Grid.h"
MapRegistryComponent::MapRegistryComponent(dae::GameObject* pOwner, Grid* pGrid)
	: Component(pOwner)
	, m_pGrid(pGrid)
{
	
}
