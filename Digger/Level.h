#pragma once
#include <Component.h>
#include <memory>

#include "Grid.h"
#include "GamemodeEnums.h"
//comps
#include <TransformComponent.h>
#include <TextureComponent.h>
#include "BagComponent.h"
#include "EnemyComponent.h"
#include "MapRegistryComponent.h"
#include "PlayerCollisionComponent.h"
#include "GemCollisionComponent.h"
#include "BagCollisionComponent.h"
#include "EnemyCollisionComponent.h"
#include "ScoreDisplayComponent.h"
#include "LivesDisplayComponent.h"
#include "ModeSelectComponent.h"
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
	LIVES,
	GAMEMODES
};

class Level : public dae::Component //todo: syntactically rename to component
{
public:
	Level(dae::GameObject* pOwner);//mainly constructs empty tiles to be ready for usage
	~Level() override = default;

	void Update(float deltaTime) override;
	void FixedUpdate() override;
	void Render() const override;

	void GoToNextLevel();
	void ReloadLevel();
	void EndGame();


	void ActivateVersus() { m_versusMode = true; };
	void ActivateCoop() { m_twoPlayerMode = true; };
	void StartGame();

	bool GetPlayingState() const { return m_playingState; };

private:


	std::unique_ptr<Grid>m_pGrid;

	std::unique_ptr<dae::GameObject> m_pPlayerOne;
	std::unique_ptr<dae::GameObject> m_pPlayerTwo;

	//level objects -> could easily be combined but i personally like seperating them
	std::vector <std::unique_ptr<dae::GameObject>> m_pGemObjects{};
	std::vector <std::unique_ptr<dae::GameObject>> m_pBagObjects{};
	std::vector <std::unique_ptr<dae::GameObject>> m_pEnemyObjects{};


	void CheckDAEVectorForDeletion(std::vector <std::unique_ptr<dae::GameObject>>& vecToCheck);

	std::map<UIElements, std::unique_ptr<dae::GameObject>> m_pUIElements{};


	dae::TransformComponent* m_pP1Transform; //save to not have to get it every loop
	dae::TransformComponent* m_pP2Transform; //save to not have to get it every loop
	void m_CreateGem(int gridPosX, int gridPosY);
	void m_CreateBag(int gridPosX, int gridPosY);
	void m_CreateEnemy(int gridPosX, int gridPosY, bool playerControlled = false);

	void m_ResetMap();

	bool m_playingState{false};
	bool m_twoPlayerMode{ false };
	bool m_versusMode{ false };


	unsigned int m_currLevel{ 0 };

	//level data
	std::vector<std::string> m_levelPathVec{};
	void m_AddLevelNames();
	void m_ShowWinScreen();
	void LoadLevelFromFile(const std::string& fileName);

	void m_OpenStartUI();

	const float m_playerMoveSpeed{ 100.f };

	void m_InitPlayerOne();
	void m_InitPlayerTwo();
	void m_InitPlayerOneControls();
	void m_InitPlayerTwoControls();
	void m_InitUI();//call after playerInitialization
};

