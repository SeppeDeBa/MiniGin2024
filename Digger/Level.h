#pragma once
#include <Minigin.h> //todo:move global width and height to its own .h
#include <memory>
#include "TileComponent.h"
#include <GameObject.h>
class Level
{
public:
	Level();//mainly constructs empty tiles to be ready for usage
	~Level();

	void Update(float deltaTime);
	void Render() const;
	void LoadLevelFromFile(const std::string& fileName);
	
	bool IsTileOpen(int x, int y) const { return tileMap[x][y]->GetComponent<TileComponent>()->IsOpen(); }

private:
	static const int m_nrRows{ 10 };//UI row not included
	static const int m_nrRowsUIIncluded{ m_nrRows + 1 }; //for ease of use
	static const int m_nrCols{ 15 };

	const float m_tileWidth{ static_cast<float>( g_windowWdith )/ static_cast<float>(m_nrCols )};
	const float m_tileHeight{ static_cast<float>(g_windowHeight) / static_cast<float>(m_nrRowsUIIncluded )};


	std::unique_ptr<dae::GameObject> tileMap[m_nrCols][m_nrRows]{};

};

