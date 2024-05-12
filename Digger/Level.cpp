#include "Level.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
Level::Level()
{
	for (int colIt{}; colIt < m_nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < m_nrRows; ++rowIt)
		{
			//would it be better here to just use a saved reference to not have to find map so much? its only on construction though
			tileMap[colIt][rowIt] = std::make_unique<dae::GameObject>();
			tileMap[colIt][rowIt]->AddComponent<dae::TransformComponent>(colIt * m_tileWidth, rowIt*m_tileHeight);
			tileMap[colIt][rowIt]->AddComponent<dae::TextureComponent>("Tile.png", false);
			tileMap[colIt][rowIt]->AddComponent<TileComponent>(colIt, rowIt, m_tileWidth, m_tileHeight );
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
			tileMap[colIt][rowIt]->Update(deltaTime);
		}
	}
}

void Level::Render() const
{
	for (int colIt{}; colIt < m_nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < m_nrRows; ++rowIt)
		{
			tileMap[colIt][rowIt]->Render();
		}
	}
}

void Level::LoadLevelFromFile(const std::string&)
{

}
