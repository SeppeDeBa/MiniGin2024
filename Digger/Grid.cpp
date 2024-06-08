#include "Grid.h"

Grid::Grid()
{
	for (int colIt{}; colIt < s_nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < s_nrRows; ++rowIt)
		{
			//would it be better here to just use a saved reference to not have to find map so much? its only on construction though
			m_pTileMap[colIt][rowIt] = std::make_unique<dae::GameObject>();
			m_pTileMap[colIt][rowIt]->AddComponent<dae::TransformComponent>(colIt * s_tileWidth, rowIt * s_tileHeight + s_tileHeight);//add offset to tileHeight for UI block
			m_pTileMap[colIt][rowIt]->AddComponent<dae::TextureComponent>("Tile.png", false);
			m_pTileMap[colIt][rowIt]->AddComponent<TileComponent>(colIt, rowIt, s_tileWidth, s_tileHeight);
		}
	}
}

void Grid::Update(float deltaTime)
{
	for (int colIt{}; colIt < s_nrCols; ++colIt) //should these "for each tile" functions be templated? or use an algo
	{
		for (int rowIt{}; rowIt < s_nrRows; ++rowIt)
		{
			m_pTileMap[colIt][rowIt]->Update(deltaTime);
		}
	}
}

void Grid::Render() const
{
	for (int colIt{}; colIt < s_nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < s_nrRows; ++rowIt)
		{
			m_pTileMap[colIt][rowIt]->Render();
		}
	}
}

bool Grid::IsTileOpenFromWorldPos(float worldPosX, float worldPosY) const
{
	return m_pTileMap[static_cast<int>(worldPosX / s_tileWidth)][static_cast<int>(worldPosY / s_tileHeight - 1)]->GetComponent<TileComponent>()->IsOpen();

}

void Grid::DigTile(float worldPosX, float worldPosY)
{
	m_pTileMap[static_cast<int>(worldPosX /s_tileWidth)][static_cast<int>(worldPosY/s_tileHeight)-1]->GetComponent<TileComponent>()->DigTile();

}

void Grid::DigTileFromGridPos(int gridX, int gridY)
{
	m_pTileMap[gridX][gridY]->GetComponent<TileComponent>()->DigTile();
}

void Grid::ResetGrid()
{
	for (int colIt{}; colIt < s_nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < s_nrRows; ++rowIt)
		{
			m_pTileMap[colIt][rowIt]->GetComponent<TileComponent>()->FillTile();
		}
	}
}

glm::vec2 Grid::GetLevelTilePosition(float worldPosX, float worldPosY)
{
	return glm::vec2(worldPosX / s_tileWidth, worldPosY / s_tileHeight -1 );//1 offset for UI layer, player needs to constrain itself to boundaries of playfield however

}

bool Grid::pointIsInGrid(glm::vec2 pointToCheck)
{
	bool isInGrid{ true };
	//up (checking tileHeight as there is 1 ui row)
	if (pointToCheck.y < s_tileHeight || pointToCheck.y > g_windowHeight) isInGrid = false;
	if (pointToCheck.x < 0.f || pointToCheck.x > g_windowWidth) isInGrid = false;
	return isInGrid;
}


