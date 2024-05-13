#pragma once
#include <Minigin.h> //todo:move global width and height to its own .h
#include <Component.h>
#include <memory>

//comps
#include "TileComponent.h"
#include <TransformComponent.h>
#include <TextureComponent.h>

//extras
#include <GameObject.h>
#include "Player.h"
#include <InputManager.h>

//commands
//#include <MoveCommand.h>
//#include "DieCommand.h"
//#include "ScoreCommand.h"


#include "commandIncludesGame.h"
#include <commandIncludesEngine.h>


//COULD I HAVE FEEDBACK:
// the scenes confused me a bit as its not made by me, and despite being a limited and easy to understand class, i preffered to make my own.
// yes its a component but it makes the owning gameObject essential a game manager. this mostly as I had troubles passing the map and it was in a component as I took (see next line)
// ~ inspiration from a unity project i worked on where it also actually was a central object.

class Level : public dae::Component //todo: syntactically rename to component
{
public:
	Level(dae::GameObject* pOwner, const std::string& startingLevelName);//mainly constructs empty tiles to be ready for usage
	~Level();

	void Update(float deltaTime);
	void Render() const;
	void LoadLevelFromFile(const std::string& fileName);
	static glm::vec2 GetLevelTilePosition(float worldPosX, float worldPosY);
	void DigTile(float worldPosX, float worldPosY);
	void DigTileFromGridPos(int gridX, int gridY);
	
	glm::vec2 GetTileSize()const { return glm::vec2{ m_tileWidth, m_tileHeight }; };

	

	bool IsTileOpen(int x, int y) const { return m_pTileMap[x][y]->GetComponent<TileComponent>()->IsOpen(); }
	bool IsTileOpenFromWorldPos(float worldPosX, float worldPosY) const;

	//public statics for other objects
	static const int m_nrRows{ 10 };//UI row not included
	static const int m_nrRowsUIIncluded{ m_nrRows + 1 }; //for ease of use
	static const int m_nrCols{ 15 };

	//make these inline to let the compiler know that the variable should always be the same, avoiding multiple definitions, useful as its being used in a static function
	inline static const float m_tileWidth{ static_cast<float>( g_windowWdith )/ static_cast<float>(m_nrCols )};
	inline static const float m_tileHeight{ static_cast<float>(g_windowHeight) / static_cast<float>(m_nrRowsUIIncluded )};
private:

	void m_InitPlayerOne();
	std::unique_ptr<dae::GameObject> m_pTileMap[m_nrCols][m_nrRows]{};
	std::unique_ptr<dae::GameObject> m_pPlayerOne;
	std::unique_ptr<dae::GameObject> m_pPlayerTwo;
	std::vector <std::unique_ptr<dae::GameObject>> m_pGemObjects{};
	std::vector <std::unique_ptr<dae::GameObject>> m_pBagObjects{};

	void m_CreateGem(int gridPosX, int gridPosY);
	void m_CreateBag(int gridPosX, int gridPosY);


};

