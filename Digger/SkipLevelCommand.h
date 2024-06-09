#pragma once
#include <Command.h>
#include <Chrono>
#include "GOCommand.h"
class Level;
class SkipLevelCommand : public dae::Command
{
public:
	SkipLevelCommand(Level* levelToManipulate)
	:m_pLevel(levelToManipulate)
	, m_lastExecuteCall(std::chrono::steady_clock::now() - std::chrono::seconds(m_commandCooldown))//do minus 2 so its instantly usable
	{};
	~SkipLevelCommand() override = default;
	void Execute(float) override;

private:
	const int m_commandCooldown{ 2 }; //could be put into another subcommand class
	Level* m_pLevel;
	std::chrono::steady_clock::time_point m_lastExecuteCall;
};

