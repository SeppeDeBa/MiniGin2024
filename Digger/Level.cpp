#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>
#include "commandIncludesGame.h"
#include <commandIncludesEngine.h>
Level::Level(dae::GameObject* pOwner, const std::string& startingLevelName)
	: dae::Component(pOwner)
{
	//init level map
	for (int colIt{}; colIt < s_nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < s_nrRows; ++rowIt)
		{
			//would it be better here to just use a saved reference to not have to find map so much? its only on construction though
			m_pTileMap[colIt][rowIt] = std::make_unique<dae::GameObject>();
			m_pTileMap[colIt][rowIt]->AddComponent<dae::TransformComponent>(colIt * s_tileWidth, rowIt* s_tileHeight + s_tileHeight);//add offset to tileHeight for UI block
			m_pTileMap[colIt][rowIt]->AddComponent<dae::TextureComponent>("Tile.png", false);
			m_pTileMap[colIt][rowIt]->AddComponent<TileComponent>(colIt, rowIt, s_tileWidth, s_tileHeight );
		}
	}
	m_InitPlayerOne();
	LoadLevelFromFile(startingLevelName);
	m_InitUI();
	//init player1

}

Level::~Level()
{

}

void Level::Update(float deltaTime)
{
	//update level (not needed for now...)
	for (int colIt{}; colIt < s_nrCols; ++colIt) //should these "for each tile" functions be templated? or use an algo
	{
		for (int rowIt{}; rowIt < s_nrRows; ++rowIt)
		{
			m_pTileMap[colIt][rowIt]->Update(deltaTime);
		}
	}
	for (const std::unique_ptr<dae::GameObject>& GO : m_pGemObjects)
	{
		GO->Update(deltaTime);
	}
	for (const std::unique_ptr<dae::GameObject>& GO : m_pBagObjects)
	{
		GO->Update(deltaTime);
	}
	for (const std::unique_ptr<dae::GameObject>& GO : m_pUIObjects)
	{
		GO->Update(deltaTime);
	}
	//update player
	m_pPlayerOne->Update(deltaTime);

	DigTile(m_pP1Transform->GetLocalPos().x, m_pP1Transform->GetLocalPos().y);

	
}

void Level::Render() const
{
	//render level
	for (int colIt{}; colIt < s_nrCols; ++colIt)
	{
		for (int rowIt{}; rowIt < s_nrRows; ++rowIt)
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
	for (const std::unique_ptr<dae::GameObject>& GO : m_pUIObjects)
	{
		GO->Render();
	}
	//render player
	m_pPlayerOne->Render();

}

void Level::LoadLevelFromFile(const std::string& fileName)
{
	char parsedGrid[s_nrRows][s_nrCols];
	//1. open file
	std::ifstream levelFile(fileName, std::ios::in);
	if (!levelFile.is_open())
	{
		std::cout << "Error opening level file" << std::endl;
		return;
	}
	//2. place in grid
	for (int i{ 0 }; i < s_nrRows; ++i)
	{
		std::string inputLine{};
		//safety checks
		if (!std::getline(levelFile, inputLine))
		{
			std::cout << "error reading lines" << std::endl;
			return;
		}
		if (inputLine.size() != s_nrCols)
		{
			std::cout << "error reading collumns in file, invalid size, must be: " << s_nrCols << std::endl;
			return;
		}
		for (int j{ 0 }; j < s_nrCols; ++j)
		{
			parsedGrid[i][j] = inputLine[j];
		}
	}
	//3. process gotten input
	for (int rowIt{ 0 }; rowIt < s_nrRows; ++rowIt)
		for (int colIt{ 0 }; colIt < s_nrCols; ++colIt)
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
				m_pPlayerOne->GetComponent<dae::TransformComponent>()->SetLocalPosition(colIt * s_tileWidth + s_tileWidth / 2.f, rowIt * s_tileHeight + s_tileHeight / 2.f + s_tileHeight);// put to center ( + offset for UI)
				m_pPlayerOne->SetEnabled(true);
				break;
			default:
				std::cout << "hit character:" << parsedGrid[rowIt][colIt] << std::endl;
				break;
			}
		}
}

glm::vec2 Level::GetLevelTilePosition(float worldPosX, float worldPosY)
{

	return glm::vec2(worldPosX / s_tileWidth, worldPosY / s_tileHeight -1 );//1 offset for UI layer, player needs to constrain itself to boundaries of playfield however
}

void Level::DigTile(float worldPosX, float worldPosY)
{
	m_pTileMap[static_cast<int>(worldPosX /s_tileWidth)][static_cast<int>(worldPosY/s_tileHeight)-1]->GetComponent<TileComponent>()->DigTile();
}

void Level::DigTileFromGridPos(int gridX, int gridY)
{
	m_pTileMap[gridX][gridY]->GetComponent<TileComponent>()->DigTile();
}

bool Level::IsTileOpenFromWorldPos(float worldPosX, float worldPosY) const
{
	//minus 1 offset on the Y as UI is an extra row not included in the tileMap
	return m_pTileMap[static_cast<int>(worldPosX /s_tileWidth)][static_cast<int>(worldPosY /s_tileHeight-1)]->GetComponent<TileComponent>()->IsOpen();
}

bool Level::pointIsInGrid(glm::vec2 pointToCheck)
{
	bool isInGrid{ true };
	//up (checking tileHeight as there is 1 ui row)
	if (pointToCheck.y < s_tileHeight || pointToCheck.y > g_windowHeight) isInGrid = false;
	if (pointToCheck.x < 0.f || pointToCheck.x > g_windowWidth) isInGrid = false;
	return isInGrid;
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
		std::make_unique<GridMoveCommand>(m_pPlayerOne.get(), moveSpeed,
			glm::vec2{ 0.f, 1.f }), dae::InputType::ISHELD);
	//input.AddKeyboardCommand(SDL_SCANCODE_UP,
	//	std::make_unique<dae::MoveCommand>(m_pPlayerOne.get(), moveSpeed,
	//		glm::vec2{ 0.f, 1.f }));


	//down
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DPadDown,
		std::make_unique<GridMoveCommand>(m_pPlayerOne.get(), moveSpeed,
			glm::vec2{ 0.f, -1.f }), dae::InputType::ISHELD);
	//input.AddKeyboardCommand(SDL_SCANCODE_DOWN,
	//	std::make_unique<dae::MoveCommand>(m_pPlayerOne.get(), moveSpeed,
	//		glm::vec2{ 0.f, -1.f }));
	//left
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DpadLeft,
		std::make_unique<GridMoveCommand>(m_pPlayerOne.get(), moveSpeed,
			glm::vec2{ -1.f, 0.f }), dae::InputType::ISHELD);
	//input.AddKeyboardCommand(SDL_SCANCODE_LEFT,
	//	std::make_unique<dae::MoveCommand>(m_pPlayerOne.get(), moveSpeed,
	//		glm::vec2{ -1.f, 0.f }));
	//right
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DPadRight,
		std::make_unique<GridMoveCommand>(m_pPlayerOne.get(), moveSpeed,
			glm::vec2{ 1.f, 0.f }), dae::InputType::ISHELD);
	//input.AddKeyboardCommand(SDL_SCANCODE_RIGHT,
	//	std::make_unique<dae::MoveCommand>(m_pPlayerOne.get(), moveSpeed,
	//		glm::vec2{ 1.f, 0.f }));
	
	
	////die
	//input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::ButtonX,
	//	std::make_unique<DieCommand>(m_pPlayerOne.get()),
	//	dae::InputType::ISUP);
	////score
	//input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::ButtonY,
	//	std::make_unique<ScoreCommand>(m_pPlayerOne.get(), 100),
	//	dae::InputType::ISUP);

	m_pP1Transform = m_pPlayerOne.get()->GetComponent<dae::TransformComponent>();
}

void Level::m_InitUI()//call after playerInitialization
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Retro.otf", 30);

	//Score
	m_pUIObjects.emplace_back(std::make_unique<dae::GameObject>());
	dae::GameObject* ScoreObject = m_pUIObjects.back().get();
	ScoreObject->AddComponent<dae::TransformComponent>(25.f, 2.f);
	ScoreObject->AddComponent<dae::TextureComponent>(false);
	ScoreObject->AddComponent<dae::TextComponent>("000000", font);
	ScoreObject->AddComponent<dae::ScoreDisplayComponent>(m_pPlayerOne->GetComponent<Player>());
}

void Level::m_CreateGem(int gridPosX, int gridPosY)
{
	m_pGemObjects.emplace_back(std::make_unique<dae::GameObject>());
	dae::GameObject* createdGem = m_pGemObjects.back().get();
	float xPos{ gridPosX * s_tileWidth + s_tileWidth / 2.f };
	float yPos{ gridPosY * s_tileHeight + s_tileHeight / 2.f + s_tileHeight }; //add offset

	createdGem->AddComponent<dae::TransformComponent>(xPos, yPos);
	createdGem->AddComponent<dae::TextureComponent>("Gem.png", true);
}

void Level::m_CreateBag(int gridPosX, int gridPosY)
{
	m_pBagObjects.emplace_back(std::make_unique<dae::GameObject>());
	dae::GameObject* createdBag = m_pBagObjects.back().get();
	float xPos{ gridPosX * s_tileWidth + s_tileWidth / 2.f };
	float yPos{ gridPosY * s_tileHeight + s_tileHeight / 2.f + s_tileHeight }; //add offset

	createdBag->AddComponent<dae::TransformComponent>(xPos, yPos);
	createdBag->AddComponent<dae::TextureComponent>("Bag.png", true);
}
