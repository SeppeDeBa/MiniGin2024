#include "Player.h"
#include "iostream"
Player::Player(dae::GameObject* pOwner, unsigned int playerNr, int startingLives)
	: Component(pOwner)
	, m_Lives(startingLives)
	//, m_Score(0)
	, m_Active(true)
	, m_PlayerNumber(playerNr)
	, m_PlayerDirection(playerDirection::Right)
{
	InitPlayerTextures(playerNr);
}

void Player::Die()
{
	//if(m_Lives > 0)
	//{
	//	--m_Lives;
	//	playerDied.Notify(m_Lives);
	//	if(m_Lives <= 0)
	//	{
	//		gameOver.Notify();//unused but putting in place for later
	//		std::cout << "Game over!" << std::endl; //replace later with a class that handles game over.
	//	}
	//}
}



int Player::GetLives() const
{
	return m_Lives;
}

int Player::GetScore() const
{
	return 0;
	//return m_Score;
}

void Player::Activate()
{
	m_Active = true;
	GetGameObject()->GetComponent<dae::TextureComponent>()->EnableDrawing();
}

void Player::Deactivate()
{
	m_Active = false;
	GetGameObject()->GetComponent<dae::TextureComponent>()->DisableDrawing();
}

void Player::UpdatePlayerDirection(const playerDirection directionToSet)
{
	if(m_PlayerDirection != directionToSet)
	{
		m_PlayerDirection = directionToSet;
		GetGameObject()->GetComponent<dae::TextureComponent>()->SetTexture(m_pTexturesMap[{m_PlayerNumber, m_PlayerDirection}]);
	}
}

void Player::InitPlayerTextures(unsigned int playerNr)
{
	std::string playerString{ "Digger" + std::to_string(playerNr) };

	//directional assign strings
	std::string upFilePath{ playerString + "U.png" };
	std::string downFilePath{ playerString + "D.png" };
	std::string leftFilePath{ playerString + "L.png" };
	std::string rightFilePath{ playerString + "R.png" };

	//assigning
	//up
	m_pTexturesMap.insert({ {playerNr, playerDirection::Up}, 
		        dae::ResourceManager::GetInstance().LoadTexture(upFilePath) });
	//down
	m_pTexturesMap.insert({ {playerNr, playerDirection::Down},
			dae::ResourceManager::GetInstance().LoadTexture(downFilePath) });
	//left
	m_pTexturesMap.insert({ {playerNr, playerDirection::Left},
			dae::ResourceManager::GetInstance().LoadTexture(leftFilePath) });
	//right
	m_pTexturesMap.insert({ {playerNr, playerDirection::Right},
		dae::ResourceManager::GetInstance().LoadTexture(rightFilePath) });

}
