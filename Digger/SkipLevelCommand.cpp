#include "SkipLevelCommand.h"
#include "Level.h"

void SkipLevelCommand::Execute(float)
{
    auto now = std::chrono::steady_clock::now();
    auto durationSinceLastExecution = std::chrono::duration_cast<std::chrono::seconds>(now - m_lastExecuteCall);

    if (durationSinceLastExecution.count() >= m_commandCooldown)
    {
        if (m_pLevel->GetPlayingState())
        {
            // Your logic here (if any)
        }
        m_pLevel->GoToNextLevel();
        m_lastExecuteCall = now; // Update the last execution time
    }
}
