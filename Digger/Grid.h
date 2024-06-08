#pragma once
#include <Minigin.h> 
#include <glm/glm.hpp>
#include "GameObject.h"
#include "TileComponent.h"

class Grid
{
public:
	Grid();
	~Grid() = default;


	void Update(float deltaTime);
	void Render() const;

	//void LoadLevelFromFile(const std::string& fileName);
	bool IsTileOpen(int x, int y) const { return m_pTileMap[x][y]->GetComponent<TileComponent>()->IsOpen(); }
	bool IsTileOpenFromWorldPos(float worldPosX, float worldPosY) const;

	//digging
	void DigTile(float worldPosX, float worldPosY);
	void DigTileFromGridPos(int gridX, int gridY);



	static glm::vec2 GetLevelTilePosition(float worldPosX, float worldPosY);
	static glm::vec2 GetTileSize() { return glm::vec2{ s_tileWidth, s_tileHeight }; };
	static bool pointIsInGrid(glm::vec2 pointToCheck);

	static const int s_nrRows{ 10 };//UI row not included
	static const int s_nrRowsUIIncluded{ s_nrRows + 1 }; //for ease of use
	static const int s_nrCols{ 15 };

	//make these inline to let the compiler know that the variable should always be the same, avoiding multiple definitions, useful as its being used in a static function
	inline static const float s_tileWidth{ static_cast<float>(g_windowWidth) / static_cast<float>(s_nrCols) };
	inline static const float s_tileHeight{ static_cast<float>(g_windowHeight) / static_cast<float>(s_nrRowsUIIncluded) };

private:
	std::unique_ptr<dae::GameObject> m_pTileMap[s_nrCols][s_nrRows]{};
};

