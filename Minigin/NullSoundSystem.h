#pragma once
#include "ISoundSystem.h"
#include <iostream>
// ISoundSystem has: 
// using sound_id = unsigned short;
class NullSoundSystem final : public ISoundSystem
{
public:
	virtual ~NullSoundSystem() = default;
	void Play(const sound_id, const float) const override {
		std::cout << "trying to play a sound when sound system is null" << std::endl;
	}

	void Pause() const override {
		std::cout << "trying to pause a file to a NULL soundsystem" << std::endl;
	}
	void Resume() const override {
		std::cout << "trying to resume a file to a NULL soundsystem" << std::endl;
	};
	void Stop() const override {
		std::cout << "trying to stop a file to a NULL soundsystem" << std::endl;
	};
	void Load(const char* filePath) override {
		std::cout << "trying to load a file to a NULL soundsystem with path: " << filePath << std::endl;
	};
};
