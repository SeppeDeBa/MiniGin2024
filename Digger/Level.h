#pragma once
#include <Component.h>
#include <memory>

#include "Grid.h"

//comps
#include <TransformComponent.h>
#include <TextureComponent.h>
#include "BagComponent.h"
#include "MapRegistryComponent.h"
//extras
#include <GameObject.h>
#include "Player.h"
#include <InputManager.h>

//commands
//#include <MoveCommand.h>
//#include "DieCommand.h"
//#include "ScoreCommand.h"



enum UIElements
{
	SCORE,
	LIVES
};

//COULD I HAVE FEEDBACK:
// the scenes confused me a bit as its not made by me, and despite being a limited and easy to understand class, i preffered to make my own.
// yes its a component but it makes the owning gameObject essential a game manager. this mostly as I had troubles passing the map and it was in a component as I took (see next line)
// ~ inspiration from a unity project i worked on where it also actually was a central object.

class Level : public dae::Component //todo: syntactically rename to component
{
public:
	Level(dae::GameObject* pOwner, const std::string& startingLevelName);//mainly constructs empty tiles to be ready for usage
	~Level() override;

	void Update(float deltaTime) override;
	void Render() const override;
	void LoadLevelFromFile(const std::string& fileName);
	//static glm::vec2 GetLevelTilePosition(float worldPosX, float worldPosY);
	//void DigTile(float worldPosX, float worldPosY);
	//void DigTileFromGridPos(int gridX, int gridY);
	
	/*glm::vec2 GetTileSize()const { return glm::vec2{ s_tileWidth, s_tileHeight }; };*/

	

	//bool IsTileOpen(int x, int y) const { return m_pTileMap[x][y]->GetComponent<TileComponent>()->IsOpen(); }
	//bool IsTileOpenFromWorldPos(float worldPosX, float worldPosY) const;

	//public statics for other objects
	//static const int s_nrRows{ 10 };//UI row not included
	//static const int s_nrRowsUIIncluded{ s_nrRows + 1 }; //for ease of use
	//static const int s_nrCols{ 15 };

	//make these inline to let the compiler know that the variable should always be the same, avoiding multiple definitions, useful as its being used in a static function
	/*inline static const float s_tileWidth{ static_cast<float>( g_windowWidth )/ static_cast<float>(s_nrCols )};
	inline static const float s_tileHeight{ static_cast<float>(g_windowHeight) / static_cast<float>(s_nrRowsUIIncluded )};*/

	
	//static bool pointIsInGrid(glm::vec2 pointToCheck);
private:


	//std::unique_ptr<dae::GameObject> m_pTileMap[s_nrCols][s_nrRows]{};
	std::unique_ptr<Grid>m_pGrid;

	std::unique_ptr<dae::GameObject> m_pPlayerOne;
	std::unique_ptr<dae::GameObject> m_pPlayerTwo;

	//level objects
	std::vector <std::unique_ptr<dae::GameObject>> m_pGemObjects{};
	std::vector <std::unique_ptr<dae::GameObject>> m_pBagObjects{};

	
	std::map<UIElements, std::unique_ptr<dae::GameObject>> m_pUIElements{};


	dae::TransformComponent* m_pP1Transform; //save to not have to get it every loop
	void m_CreateGem(int gridPosX, int gridPosY);
	void m_CreateBag(int gridPosX, int gridPosY);


	void m_InitPlayerOne();
	void m_InitUI();//call after playerInitialization
};

