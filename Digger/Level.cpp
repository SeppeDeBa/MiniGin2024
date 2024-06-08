#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>
#include "commandIncludesGame.h"
#include <commandIncludesEngine.h>
Level::Level(dae::GameObject* pOwner)
	: dae::Component(pOwner)
	, m_pGrid(std::make_unique<Grid>())
{
	//init level map
	m_AddLevelNames();
	m_InitUI();
	m_InitPlayerOne();
	m_InitPlayerTwo();
	GoToNextLevel();
	m_InitPlayerTwoControls();
	//init player1

}

Level::~Level()
{

}

void Level::Update(float deltaTime)
{

	m_pGrid->Update(deltaTime);

	for (const std::unique_ptr<dae::GameObject>& GO : m_pGemObjects)
	{
		GO->Update(deltaTime);
	}
	for (const std::unique_ptr<dae::GameObject>& GO : m_pBagObjects)
	{
		GO->Update(deltaTime);
	}

	for (const auto& [key, value] : m_pUIElements)
	{
		value->Update(deltaTime);
	}
	//update player
	m_pPlayerOne->Update(deltaTime);
	m_pPlayerTwo->Update(deltaTime);

	m_pGrid->DigTile(m_pP1Transform->GetLocalPos().x, m_pP1Transform->GetLocalPos().y);
	if(m_twoPlayerMode)	m_pGrid->DigTile(m_pP2Transform->GetLocalPos().x, m_pP2Transform->GetLocalPos().y);


	//deletions
	CheckDAEVectorForDeletion(m_pGemObjects);
	CheckDAEVectorForDeletion(m_pBagObjects);
}

void Level::FixedUpdate()
{
	for (const std::unique_ptr<dae::GameObject>& GO : m_pBagObjects)
	{
		GO->FixedUpdate();
	}

	m_pPlayerOne->FixedUpdate();
	m_pPlayerTwo->FixedUpdate();
}

void Level::Render() const
{
	//render level
	m_pGrid->Render();
	//render gems
	for (const std::unique_ptr<dae::GameObject>& GO : m_pGemObjects)
	{
		GO->Render();
	}
	for (const std::unique_ptr<dae::GameObject>& GO : m_pBagObjects)
	{
		GO->Render();
	}
	for(const auto& [key, value] : m_pUIElements)
	{
		value->Render();
	}
	//render player
	m_pPlayerOne->Render();
	m_pPlayerTwo->Render();

}

void Level::LoadLevelFromFile(const std::string& fileName)
{
	m_ResetMap();
	char parsedGrid[Grid::s_nrRows][Grid::s_nrCols];
	//1. open file
	std::ifstream levelFile(fileName, std::ios::in);
	if (!levelFile.is_open())
	{
		std::cout << "Error opening level file" << std::endl;
		return;
	}
	//2. place in grid
	for (int i{ 0 }; i < Grid::s_nrRows; ++i)
	{
		std::string inputLine{};
		//safety checks
		if (!std::getline(levelFile, inputLine))
		{
			std::cout << "error reading lines" << std::endl;
			return;
		}
		if (inputLine.size() != Grid::s_nrCols)
		{
			std::cout << "error reading collumns in file, invalid size, must be: " << Grid::s_nrCols << std::endl;
			return;
		}
		for (int j{ 0 }; j < Grid::s_nrCols; ++j)
		{
			parsedGrid[i][j] = inputLine[j];
		}
	}
	//3. process gotten input
	for (int rowIt{ 0 }; rowIt < Grid::s_nrRows; ++rowIt)
		for (int colIt{ 0 }; colIt < Grid::s_nrCols; ++colIt)
		{
			switch (parsedGrid[rowIt][colIt])
			{
			case 'O':
				m_pGrid->DigTileFromGridPos(colIt, rowIt);
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
				m_pGrid->DigTileFromGridPos(colIt, rowIt);
				m_pPlayerOne->GetComponent<dae::TransformComponent>()->SetLocalPosition(colIt * Grid::s_tileWidth + Grid::s_tileWidth / 2.f, rowIt * Grid::s_tileHeight + Grid::s_tileHeight / 2.f + Grid::s_tileHeight);// put to center ( + offset for UI)
				m_pPlayerOne->SetEnabled(true);
				break;
			case 'T':
				m_pGrid->DigTileFromGridPos(colIt, rowIt);
				if(m_twoPlayerMode)
				{
				m_pPlayerTwo->GetComponent<dae::TransformComponent>()->SetLocalPosition(colIt * Grid::s_tileWidth + Grid::s_tileWidth / 2.f, rowIt * Grid::s_tileHeight + Grid::s_tileHeight / 2.f + Grid::s_tileHeight);// put to center ( + offset for UI)
				m_pPlayerTwo->SetEnabled(true);
				}
				break;
			default:
				std::cout << "hit character:" << parsedGrid[rowIt][colIt] << std::endl;
				break;
			}
		}
}

void Level::GoToNextLevel()
{
	std::cout << "Loading level: " << m_currLevel << std::endl;
	const unsigned int amtOfLevels{ static_cast<unsigned int>(m_levelPathVec.size()) };
	if (m_currLevel>= amtOfLevels) //check if next would be not existing, thus finishing the game
	{
		m_ShowWinScreen();
	}
	else
	{
		LoadLevelFromFile(m_levelPathVec[m_currLevel]);
	}
	++m_currLevel;
	m_currLevel %= amtOfLevels+1;
}


void Level::m_AddLevelNames() 
{
	m_levelPathVec.push_back("../Data/Level1.txt");
	m_levelPathVec.push_back("../Data/Level2.txt");
	m_levelPathVec.push_back("../Data/Level3.txt");
}

void Level::m_ShowWinScreen()
{
	std::cout << "YAY YOU WON" << std::endl;
}

void Level::m_InitPlayerOne()
{
	//1. init ptr
	m_pPlayerOne = std::make_unique<dae::GameObject>();
	
	//dae::GameObject* pGOPlayer1 = new dae::GameObject{};
	//2. build up GO
	m_pPlayerOne->AddComponent<dae::TransformComponent>(0.f, 0.f);
	m_pPlayerOne->AddComponent<dae::TextureComponent>("Digger0R.png", true);
	m_pPlayerOne->AddComponent<Player>(0);
	m_pPlayerOne->AddComponent<PlayerCollisionComponent>();
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




	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::Start,
		std::make_unique<SkipLevelCommand>(this), dae::InputType::ISDOWN);

	//m_pUIObjects[UIElementLookupIndex::lives]->GetComponent<dae::ScoreDisplayComponent>()->AssignPlayerOne(m_pPlayerOne->GetComponent<Player>());


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

void Level::m_InitPlayerTwo()
{
	//1. init ptr
	m_pPlayerTwo = std::make_unique<dae::GameObject>();

	//2. build up GO
	m_pPlayerTwo->AddComponent<dae::TransformComponent>(0.f, 0.f);
	m_pPlayerTwo->AddComponent<dae::TextureComponent>("Digger1R.png", true);
	m_pPlayerTwo->AddComponent<Player>(1);
	m_pPlayerOne->AddComponent<PlayerCollisionComponent>();


	m_pP2Transform = m_pPlayerTwo.get()->GetComponent<dae::TransformComponent>();
	m_pPlayerTwo->SetEnabled(false);
}

void Level::m_InitPlayerTwoControls()
{
	//up
	auto& input = dae::InputManager::GetInstance();
	const unsigned int controllerTwo{ 1 };
	//==PLAYER ONE
	const float moveSpeed{ 100.f };
	input.AddConsoleCommand(controllerTwo, dae::Controller::ControllerButton::DpadUp,
		std::make_unique<GridMoveCommand>(m_pPlayerTwo.get(), moveSpeed,
			glm::vec2{ 0.f, 1.f }), dae::InputType::ISHELD);



	//down
	input.AddConsoleCommand(controllerTwo, dae::Controller::ControllerButton::DPadDown,
		std::make_unique<GridMoveCommand>(m_pPlayerTwo.get(), moveSpeed,
			glm::vec2{ 0.f, -1.f }), dae::InputType::ISHELD);

	//left
	input.AddConsoleCommand(controllerTwo, dae::Controller::ControllerButton::DpadLeft,
		std::make_unique<GridMoveCommand>(m_pPlayerTwo.get(), moveSpeed,
			glm::vec2{ -1.f, 0.f }), dae::InputType::ISHELD);

	//right
	input.AddConsoleCommand(controllerTwo, dae::Controller::ControllerButton::DPadRight,
		std::make_unique<GridMoveCommand>(m_pPlayerTwo.get(), moveSpeed,
			glm::vec2{ 1.f, 0.f }), dae::InputType::ISHELD);
}

void Level::m_InitUI()//call after playerInitialization
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Retro.otf", 30);

	//Score
	std::unique_ptr<dae::GameObject> ScoreObject = std::make_unique<dae::GameObject>();

	ScoreObject->AddComponent<dae::TransformComponent>(25.f, 2.f);
	ScoreObject->AddComponent<dae::TextureComponent>(false);
	ScoreObject->AddComponent<dae::TextComponent>("000000", font);
	ScoreObject->AddComponent<ScoreDisplayComponent>();

	m_pUIElements.insert({ UIElements::SCORE, std::move(ScoreObject) });

}

void Level::CheckDAEVectorForDeletion(std::vector<std::unique_ptr<dae::GameObject>>& vecToCheck)
{
	auto it = vecToCheck.begin();
	while (it != vecToCheck.end())
	{
		if ((*it)->IsMarkedForDeletion())
		{
			it = vecToCheck.erase(it); // delete and remove from vector and advance iterator
		}
		else
		{
			++it;
		}
	}
}

void Level::m_CreateGem(int gridPosX, int gridPosY)
{
	m_pGemObjects.emplace_back(std::make_unique<dae::GameObject>());
	dae::GameObject* createdGem = m_pGemObjects.back().get();
	float xPos{ gridPosX * Grid::s_tileWidth + Grid::s_tileWidth / 2.f };
	float yPos{ gridPosY * Grid::s_tileHeight + Grid::s_tileHeight / 2.f + Grid::s_tileHeight }; //add offset

	createdGem->AddComponent<dae::TransformComponent>(xPos, yPos);
	createdGem->AddComponent<dae::TextureComponent>("Gem.png", true);
	createdGem->AddComponent<GemCollisionComponent>(m_pUIElements[UIElements::SCORE].get()->GetComponent<ScoreDisplayComponent>());
}

void Level::m_CreateBag(int gridPosX, int gridPosY)
{
	m_pBagObjects.emplace_back(std::make_unique<dae::GameObject>());
	dae::GameObject* createdBag = m_pBagObjects.back().get();
	float xPos{ gridPosX * Grid::s_tileWidth + Grid::s_tileWidth / 2.f };
	float yPos{ gridPosY * Grid::s_tileHeight + Grid::s_tileHeight / 2.f + Grid::s_tileHeight }; //add offset

	createdBag->AddComponent<dae::TransformComponent>(xPos, yPos);
	createdBag->AddComponent<dae::TextureComponent>("Bag.png", true);
	createdBag->AddComponent<MapRegistryComponent>(m_pGrid.get());
	createdBag->AddComponent<BagComponent>();
	createdBag->AddComponent<BagCollisionComponent>(m_pUIElements[UIElements::SCORE].get()->GetComponent<ScoreDisplayComponent>());
}

void Level::m_ResetMap()
{
	m_pGrid->ResetGrid();
	m_pGemObjects.clear();
	m_pBagObjects.clear();
	m_pPlayerOne->SetEnabled(false);
	m_pPlayerTwo->SetEnabled(false);
}
