#pragma once
#include <map>

#include "Component.h"
#include "TextureComponent.h"
#include "Subject.h"
	enum playerDirection
	{
		Up,
		Down,
		Left,
		Right
	};

	class Player final: public dae::Component //todo: might not have to be final if adding implementation for being enemies? have to give it some thought
	{
	public:
		Player(dae::GameObject* pOwner, unsigned int playerNr, int startingLives = 3);
		~Player() override = default;

		void Die();

	

		int GetLives() const;//needed for lives display
		int GetScore() const;


		void Activate();
		void Deactivate();

		void UpdatePlayerDirection(const playerDirection directionToSet);


	private:
		using PlayerDirection = std::pair<unsigned int, playerDirection>;
		std::map<PlayerDirection, std::shared_ptr<dae::Texture2D>> m_pTexturesMap{};
		playerDirection m_PlayerDirection;
		int m_Lives;
		/*int m_Score;*/
		bool m_Active;
		unsigned int m_PlayerNumber;

		void InitPlayerTextures(unsigned int playerNr);
	};


