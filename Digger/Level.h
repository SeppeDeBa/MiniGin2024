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

class Level : public dae::Component //todo: syntactically rename to component
{
public:
	Level(dae::GameObject* pOwner);//mainly constructs empty tiles to be ready for usage
	~Level() override;

	void Update(float deltaTime) override;
	void FixedUpdate() override;
	void Render() const override;

	void GoToNextLevel();
private:


	std::unique_ptr<Grid>m_pGrid;

	std::unique_ptr<dae::GameObject> m_pPlayerOne;
	std::unique_ptr<dae::GameObject> m_pPlayerTwo;

	//level objects
	std::vector <std::unique_ptr<dae::GameObject>> m_pGemObjects{};
	std::vector <std::unique_ptr<dae::GameObject>> m_pBagObjects{};
	std::vector <std::unique_ptr<dae::GameObject>> m_pEnemyObjects{};


	void CheckDAEVectorForDeletion(std::vector <std::unique_ptr<dae::GameObject>>& vecToCheck);

	std::map<UIElements, std::unique_ptr<dae::GameObject>> m_pUIElements{};


	dae::TransformComponent* m_pP1Transform; //save to not have to get it every loop
	dae::TransformComponent* m_pP2Transform; //save to not have to get it every loop
	void m_CreateGem(int gridPosX, int gridPosY);
	void m_CreateBag(int gridPosX, int gridPosY);


	void m_ResetMap();

	bool m_playingState{};
	bool m_twoPlayerMode{ false };
	bool m_versusMode{ false };

	unsigned int m_currLevel{ 0 };

	//level data
	std::vector<std::string> m_levelPathVec{};
	void m_AddLevelNames();
	void m_ShowWinScreen();
	void LoadLevelFromFile(const std::string& fileName);

	void m_InitPlayerOne();
	void m_InitPlayerTwo();
	void m_InitPlayerTwoControls();
	void m_InitUI();//call after playerInitialization
};

