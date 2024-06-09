#pragma once

#include <Command.h>
class ModeSelectComponent;
class GamemodeSelectorCommand : public dae::Command
{
public:
	GamemodeSelectorCommand(ModeSelectComponent* pModeSelector, int inputType);
	~GamemodeSelectorCommand() override = default;
	void Execute(float ) override;

private:
	ModeSelectComponent* m_pModeSelectComp{};
	int m_inputType;
};

