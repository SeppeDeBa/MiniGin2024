#include "Level.h"

Level::Level(dae::GameObject* pOwner)
	: dae::Component(pOwner)
{
	for (int colIt{}; colIt < m_nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < m_nrRows; ++rowIt)
		{
			//would it be better here to just use a saved reference to not have to find map so much? its only on construction though
			m_pTileMap[colIt][rowIt] = std::make_unique<dae::GameObject>();
			m_pTileMap[colIt][rowIt]->AddComponent<dae::TransformComponent>(colIt * m_tileWidth, rowIt*m_tileHeight);
			m_pTileMap[colIt][rowIt]->AddComponent<dae::TextureComponent>("Tile.png", false);
			m_pTileMap[colIt][rowIt]->AddComponent<TileComponent>(colIt, rowIt, m_tileWidth, m_tileHeight );
		}
	}
}

Level::~Level()
{

}

void Level::Update(float deltaTime)
{
	for (int colIt{}; colIt < m_nrCols; ++colIt) //should these "for each tile" functions be templated? or use an algo
	{
		for (int rowIt{}; rowIt < m_nrRows; ++rowIt)
		{
			m_pTileMap[colIt][rowIt]->Update(deltaTime);
		}
	}
}

void Level::Render() const
{
	for (int colIt{}; colIt < m_nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < m_nrRows; ++rowIt)
		{
			m_pTileMap[colIt][rowIt]->Render();
		}
	}
}

void Level::LoadLevelFromFile(const std::string&)
{

}

glm::vec2 Level::GetLevelTilePosition(float worldPosX, float worldPosY)
{

	return glm::vec2(worldPosX / m_tileWidth, worldPosY / m_tileHeight);
}

void Level::DigTile(float worldPosX, float worldPosY)
{
	m_pTileMap[static_cast<int>(worldPosX /m_tileWidth)][static_cast<int>(worldPosY/m_tileHeight)]->GetComponent<TileComponent>()->DigTile();
}

bool Level::IsTileOpenFromWorldPos(float worldPosX, float worldPosY) const
{
	//minus 1 offset on the Y as UI is an extra row not included in the tileMap
	return m_pTileMap[static_cast<int>(worldPosX /m_tileWidth)][static_cast<int>(worldPosY /m_tileHeight-1)]->GetComponent<TileComponent>()->IsOpen();
}
