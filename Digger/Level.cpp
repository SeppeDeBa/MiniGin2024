#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>

Level::Level(dae::GameObject* pOwner, const std::string& startingLevelName)
	: dae::Component(pOwner)
{
	//init level map
	for (int colIt{}; colIt < m_nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < m_nrRows; ++rowIt)
		{
			//would it be better here to just use a saved reference to not have to find map so much? its only on construction though
			m_pTileMap[colIt][rowIt] = std::make_unique<dae::GameObject>();
			m_pTileMap[colIt][rowIt]->AddComponent<dae::TransformComponent>(colIt * m_tileWidth, rowIt*m_tileHeight + m_tileHeight);//add offset to tileHeight for UI block
			m_pTileMap[colIt][rowIt]->AddComponent<dae::TextureComponent>("Tile.png", false);
			m_pTileMap[colIt][rowIt]->AddComponent<TileComponent>(colIt, rowIt, m_tileWidth, m_tileHeight );
		}
	}
	m_InitPlayerOne();
	LoadLevelFromFile(startingLevelName);
	//init player1

}

Level::~Level()
{

}

void Level::Update(float deltaTime)
{
	//update level (not needed for now...)
	//for (int colIt{}; colIt < m_nrCols; ++colIt) //should these "for each tile" functions be templated? or use an algo
	//{
	//	for (int rowIt{}; rowIt < m_nrRows; ++rowIt)
	//	{
	//		m_pTileMap[colIt][rowIt]->Update(deltaTime);
	//	}
	//}
	//update player
	m_pPlayerOne->Update(deltaTime);
}

void Level::Render() const
{
	//render level
	for (int colIt{}; colIt < m_nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < m_nrRows; ++rowIt)
		{
			m_pTileMap[colIt][rowIt]->Render();
		}
	}
	//render gems
	for (const std::unique_ptr<dae::GameObject>& GO : m_pGemObjects)
	{
		GO->Render();
	}
	for (const std::unique_ptr<dae::GameObject>& GO : m_pBagObjects)
	{
		GO->Render();
	}
	//render player
	m_pPlayerOne->Render();

}

void Level::LoadLevelFromFile(const std::string& fileName)
{
	char parsedGrid[m_nrCols][m_nrRows];
	//1. open file
	std::ifstream levelFile(fileName);
	if (!levelFile.is_open())
	{
		std::cout << "Error opening level file" << std::endl;
		return;
	}
	//2. place in grid
	for (int i{ 0 }; i < m_nrRows; ++i)
	{
		std::string inputLine{};
		//safety checks
		if (!std::getline(levelFile, inputLine))
		{
			std::cout << "error reading lines" << std::endl;
			return;
		}
		else if (inputLine.size() != m_nrCols)
		{
			std::cout << "error reading collumns in file, invalid size, must be: " << m_nrCols << std::endl;
			return;
		}
		for (int j{ 0 }; j < m_nrCols; ++j)
		{
			parsedGrid[i][j] = inputLine[j];
		}
	}
	//3. process gotten input
	for (int rowIt{ 0 }; rowIt < m_nrRows; ++rowIt)
		for (int colIt{ 0 }; colIt < m_nrCols; ++rowIt)
		{
			switch (parsedGrid[rowIt][colIt])
			{
			case 'O':
				DigTileFromGridPos(colIt, rowIt);
				break;
			case 'X':
				//do nothing as its by default a wall
				break;
			case 'B':
				//spawn bag
				m_CreateBag(colIt, rowIt);
				break;
			case 'G':
				//spawn gem
				m_CreateGem(colIt, rowIt);
				break;
			case 'S':
				DigTileFromGridPos(colIt, rowIt);
				m_pPlayerOne->GetComponent<dae::TransformComponent>()->SetLocalPosition(colIt * m_tileWidth + m_tileWidth / 2.f, rowIt * m_tileHeight + m_tileHeight / 2.f + m_tileHeight);// put to center ( + offset for UI)
				m_pPlayerOne->SetEnabled(true);
				break;
			}
		}



}

glm::vec2 Level::GetLevelTilePosition(float worldPosX, float worldPosY)
{

	return glm::vec2(worldPosX / m_tileWidth, worldPosY / m_tileHeight -1 );//1 offset for UI layer, player needs to constrain itself to boundaries of playfield however
}

void Level::DigTile(float worldPosX, float worldPosY)
{
	m_pTileMap[static_cast<int>(worldPosX /m_tileWidth)][static_cast<int>(worldPosY/m_tileHeight)]->GetComponent<TileComponent>()->DigTile();
}

void Level::DigTileFromGridPos(int gridX, int gridY)
{
	m_pTileMap[gridX][gridY]->GetComponent<TileComponent>()->DigTile();
}

bool Level::IsTileOpenFromWorldPos(float worldPosX, float worldPosY) const
{
	//minus 1 offset on the Y as UI is an extra row not included in the tileMap
	return m_pTileMap[static_cast<int>(worldPosX /m_tileWidth)][static_cast<int>(worldPosY /m_tileHeight-1)]->GetComponent<TileComponent>()->IsOpen();
}

void Level::m_InitPlayerOne()
{
	//1. init ptr
	m_pPlayerOne = std::make_unique<dae::GameObject>();
	
	//dae::GameObject* pGOPlayer1 = new dae::GameObject{};
	//2. build up GO
	m_pPlayerOne->AddComponent<dae::TransformComponent>(0.f, 0.f);
	m_pPlayerOne->AddComponent<dae::TextureComponent>("Digger.png", true);
	m_pPlayerOne->AddComponent<Player>();
	//GORotatorOne->AddComponent<dae::RotatorComponent>(100.f, 90.f, true, 0.f);
	//GORotatorOne->SetParent(GOCenterPoint, false);

	auto& input = dae::InputManager::GetInstance();
	const unsigned int controllerOne{ 0 };
	//==PLAYER ONE
	const float moveSpeed{ 100.f };
	//up
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DpadUp,
		std::make_unique<dae::MoveCommand>(m_pPlayerOne.get(), moveSpeed,
			glm::vec2{ 0.f, 1.f }), dae::InputType::ISHELD);

	//down
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DPadDown,
		std::make_unique<dae::MoveCommand>(m_pPlayerOne.get(), moveSpeed,
			glm::vec2{ 0.f, -1.f }), dae::InputType::ISHELD);

	//left
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DpadLeft,
		std::make_unique<dae::MoveCommand>(m_pPlayerOne.get(), moveSpeed,
			glm::vec2{ -1.f, 0.f }), dae::InputType::ISHELD);

	//right
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DPadRight,
		std::make_unique<dae::MoveCommand>(m_pPlayerOne.get(), moveSpeed,
			glm::vec2{ 1.f, 0.f }), dae::InputType::ISHELD);

	////die
	//input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::ButtonX,
	//	std::make_unique<DieCommand>(m_pPlayerOne.get()),
	//	dae::InputType::ISUP);
	////score
	//input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::ButtonY,
	//	std::make_unique<ScoreCommand>(m_pPlayerOne.get(), 100),
	//	dae::InputType::ISUP);

}

void Level::m_CreateGem(int gridPosX, int gridPosY)
{
	m_pGemObjects.emplace_back(std::make_unique<dae::GameObject>());
	dae::GameObject* createdGem = m_pGemObjects.back().get();
	float xPos{ gridPosX * m_tileWidth + m_tileWidth / 2.f };
	float yPos{ gridPosY * m_tileHeight + m_tileHeight / 2.f + m_tileHeight }; //add offset

	createdGem->AddComponent<dae::TransformComponent>(xPos, yPos);
	createdGem->AddComponent<dae::TextureComponent>("Gem.png", true);
}

void Level::m_CreateBag(int gridPosX, int gridPosY)
{
	m_pBagObjects.emplace_back(std::make_unique<dae::GameObject>());
	dae::GameObject* createdBag = m_pBagObjects.back().get();
	float xPos{ gridPosX * m_tileWidth + m_tileWidth / 2.f };
	float yPos{ gridPosY * m_tileHeight + m_tileHeight / 2.f + m_tileHeight }; //add offset

	createdBag->AddComponent<dae::TransformComponent>(xPos, yPos);
	createdBag->AddComponent<dae::TextureComponent>("Bag.png", true);
}
