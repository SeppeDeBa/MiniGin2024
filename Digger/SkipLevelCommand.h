#pragma once
#include <Command.h>

#include "GOCommand.h"
class Level;
class SkipLevelCommand : public dae::Command
{
public:
	SkipLevelCommand(Level* levelToManipulate) :m_pLevel(levelToManipulate) {};
	~SkipLevelCommand() override = default;
	void Execute(float) override;

private:
	Level* m_pLevel;
};

