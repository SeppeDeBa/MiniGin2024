#pragma once
#include "Component.h"

class Grid;

#include <GameObject.h>
class MapRegistryComponent : public dae::Component
{
public:
	MapRegistryComponent(dae::GameObject* pOwner, Grid* pGrid);
	~MapRegistryComponent() override = default;

	Grid const* GetGrid() const { return m_pGrid; };
	//bool IsTileOpen(int x, int y) const
	//{ return m_pGrid[x][y]->GetComponent<TileComponent>()->IsOpen(); }
	//bool IsTileOpenFromWorldPos(float worldPosX, float worldPosY) const;
private:
	Grid* m_pGrid{nullptr};
};

