#include "NullSoundSystem.h"
#include "SoundServiceLocator.h"
std::unique_ptr<ISoundSystem> SoundServiceLocator::m_SSInstance{ std::make_unique<NullSoundSystem>() };
