#pragma once
#include <Minigin.h> //todo:move global width and height to its own .h
#include <Component.h>
#include <memory>
#include "TileComponent.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <GameObject.h>
class Level : public dae::Component //todo: syntactically rename to component
{
public:
	Level(dae::GameObject* pOwner);//mainly constructs empty tiles to be ready for usage
	~Level();

	void Update(float deltaTime);
	void Render() const;
	void LoadLevelFromFile(const std::string& fileName);
	glm::vec2 GetLevelTilePosition(float worldPosX, float worldPosY);
	void DigTile(float worldPosX, float worldPosY);

	
	glm::vec2 GetTileSize()const { return glm::vec2{ m_tileWidth, m_tileHeight }; };


	bool IsTileOpen(int x, int y) const { return m_pTileMap[x][y]->GetComponent<TileComponent>()->IsOpen(); }
	bool IsTileOpenFromWorldPos(float worldPosX, float worldPosY) const;
private:
	static const int m_nrRows{ 10 };//UI row not included
	static const int m_nrRowsUIIncluded{ m_nrRows + 1 }; //for ease of use
	static const int m_nrCols{ 15 };

	const float m_tileWidth{ static_cast<float>( g_windowWdith )/ static_cast<float>(m_nrCols )};
	const float m_tileHeight{ static_cast<float>(g_windowHeight) / static_cast<float>(m_nrRowsUIIncluded )};


	std::unique_ptr<dae::GameObject> m_pTileMap[m_nrCols][m_nrRows]{};

};

