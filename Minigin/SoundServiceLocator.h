#pragma once
#include "ISoundSystem.h"
#include <memory>
#include "NullSoundSystem.h"
class SoundServiceLocator final
{
private:
	static std::unique_ptr<ISoundSystem> m_SSInstance;
public:
	static ISoundSystem& Get_Sound_System() {
		return *m_SSInstance;
	};
	static void Register_Sound_System(std::unique_ptr<ISoundSystem>&& soundSystemPtr) {
		m_SSInstance = soundSystemPtr == nullptr ? std::make_unique<NullSoundSystem>()
			: std::move(soundSystemPtr);
	}
};

