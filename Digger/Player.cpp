#include "Player.h"
#include "iostream"
Player::Player(GameObject* pOwner, int startingLives)
	:Component(pOwner)
	, m_Lives(startingLives)
	, m_Score(0)
{

}

void Player::Die()
{
	if(m_Lives > 0)
	{
		--m_Lives;
		playerDied.Notify(m_Lives);
		if(m_Lives <= 0)
		{
			gameOver.Notify();//unused but putting in place for later
			std::cout << "Game over!" << std::endl; //replace later with a class that handles game over.
		}
	}
	
}

void Player::Score(int scoreGained)
{
	m_Score += scoreGained;
	scoreChanged.Notify(m_Score);
	if (m_Score >= m_ScoreToWin)
	{
		std::cout << "pinging steam achievement system" << std::endl;
		//pass ping to steam achievement system, including the steam sdk did not work and i lost too much time on trying to fix my static library, thats my fault
	}
}

int Player::GetLives() const
{
	return m_Lives;
}

int Player::GetScore() const
{
	return m_Score;
}
