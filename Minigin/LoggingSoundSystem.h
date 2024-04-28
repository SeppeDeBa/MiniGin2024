#pragma once
#include "ISoundSystem.h"
#include <memory>
#include <iostream>
// ISoundSystem has: 
// using sound_id = unsigned short;
class LoggingSoundSystem final : public ISoundSystem
{
private:
	std::unique_ptr<ISoundSystem> m_pRealSoundSystem;
public:
	LoggingSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystemPtr)
		: m_pRealSoundSystem{ std::move(soundSystemPtr) }
	{};
	virtual ~LoggingSoundSystem() = default;

	void Play(const sound_id soundID) const override {
		m_pRealSoundSystem->Play(soundID);
		std::cout << "playing sound id: " << soundID << std::endl;
	}
	virtual void Pause() const override {
		m_pRealSoundSystem->Pause();
	};
	virtual void Resume() const override {
		m_pRealSoundSystem->Resume();
	};
	virtual void Stop() const override {
		m_pRealSoundSystem->Stop();
	};
	virtual void Load(const char* filePath) override {
		m_pRealSoundSystem->Load(filePath);
	};
};
