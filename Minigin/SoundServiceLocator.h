#pragma once
#include "ISoundSystem.h"
#include <memory>
#include "NullSoundSystem.h"
#include <iostream>
class SoundServiceLocator final
{
private:
	static std::unique_ptr<ISoundSystem> m_SSInstance;
public:
	static ISoundSystem& Get_Sound_System() {
		return *m_SSInstance;
	};
	static void Register_Sound_System(std::unique_ptr<ISoundSystem>&& soundSystemPtr) {
		if (soundSystemPtr == nullptr)
		{
			m_SSInstance = std::make_unique<NullSoundSystem>();
			std::cout << "using nullsoundsystem as soundsystemPtr was invalid" << std::endl;
		}
		else
		{
			m_SSInstance = std::move(soundSystemPtr);
			std::cout << "creating a valid soundsystem" << std::endl;
		}
		//split this up for clarity
		//m_SSInstance = soundSystemPtr == nullptr ? std::make_unique<NullSoundSystem>()
		//	: std::move(soundSystemPtr);
	}
};

