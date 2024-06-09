#pragma once
#include "Component.h"
#include "Level.h"
#include "GamemodeSelectorCommand.h"
enum GameMode
{
	SOLO = 0,
	DUO = 1,
	VS = 2
};
class ModeSelectComponent : public dae::Component
{
public:
	ModeSelectComponent(dae::GameObject* pOwner, Level* pLevelToStart);
	~ModeSelectComponent() override;

	void SelectNextGameMode();
	void SelectPreviousGameMode();
	void ConfirmGameMode();

	ModeSelectComponent(const ModeSelectComponent& other) = delete;
	ModeSelectComponent(ModeSelectComponent&& other) = delete;
	ModeSelectComponent& operator=(const ModeSelectComponent& other) = delete;
	ModeSelectComponent& operator=(ModeSelectComponent&& other) = delete;

private:

	std::string m_GetStringFromCurrentMode() const;
	void m_UpdateDisplay(const std::string& outputString);
	void m_UpdateDisplayToCurrentGM();
	dae::TextComponent* m_pTextComponent;
	Level* m_pLevel;

	
	void m_InitControls();
	GameMode m_currentGamemode{SOLO};
	
};

