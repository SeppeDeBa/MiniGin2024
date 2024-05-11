#include "Level.h"

Level::Level()
{
	for (int colIt{}; colIt < nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < nrRows; ++rowIt)
		{
			tileMap[colIt][rowIt] = std::make_unique<dae::GameObject>();
			tileMap[colIt][rowIt]->AddComponent(tileComponent)
		}
	}
}

Level::~Level()
{

}

void Level::Update(float deltaTime)
{
}

void Level::Render() const
{
}
