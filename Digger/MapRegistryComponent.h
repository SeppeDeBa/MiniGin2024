#pragma once
#include "Component.h"
#include "Grid.h"
#include <GameObject.h>
class MapRegistryComponent : public dae::Component
{
	MapRegistryComponent(dae::GameObject* pOwner, dae::GameObject* grid2Dptr, int rows = Grid::s_nrRows, int cols = Grid::s_nrCols);
	~MapRegistryComponent() override = default;


	//bool IsTileOpen(int x, int y) const
	//{ return m_pGrid[x][y]->GetComponent<TileComponent>()->IsOpen(); }
	bool IsTileOpenFromWorldPos(float worldPosX, float worldPosY) const;
private:
	dae::GameObject* m_pGrid;

	const int m_rowCount;
	const int m_colCount;
};

