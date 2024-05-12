#pragma once
#include "Component.h"
#include "TextureComponent.h"
#include "Subject.h"

	class Player final: public dae::Component //todo: might not have to be final if adding implementation for being enemies? have to give it some thought
	{
	public:
		Player(dae::GameObject* pOwner, int startingLives = 3);
		~Player() = default;

		void Die();

		void Score(int scoreGained);

		int GetLives() const;//needed for lives display
		int GetScore() const;

		void Activate();
		void Deactivate();

		Subject<int> playerDied;
		Subject<int> scoreChanged;
		Subject<> gameOver;//unused but already putting in place for later
	private:
		int m_Lives;
		int m_Score;
		bool m_Active;
		int m_ScoreToWin{ 500 };
	};


