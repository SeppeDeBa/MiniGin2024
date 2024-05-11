#pragma once
#include <Minigin.h> //todo:move global width and height to its own .h
#include <memory>
#include "Tile.h"
#include <GameObject.h>
class Level
{
public:
	Level();//mainly constructs empty tiles to be ready for usage
	~Level();

	void Update(float deltaTime);
	void Render() const;
	void LoadLevelFromFile(const std::string& fileName);


private:
	static const int nrRows{ 10 };//UI row not included
	static const int nrRowsUIIncluded{ nrRows + 1 }; //for ease of use
	static const int nrCols{ 15 };

	const float tileHeight{ g_windowHeight / nrRows + 1 }; //+1 for UI
	const float tileWidth{ g_windowWdith / nrCols };


	std::unique_ptr<dae::GameObject> tileMap[nrCols][nrRows]{};

};

