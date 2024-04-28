#pragma once
#include "ISoundSystem.h"
#include <memory>
class SoundSystem final : public ISoundSystem
{
	class SoundSystemImpl;
	std::unique_ptr<SoundSystemImpl> m_pImpl;
public:
	SoundSystem();
	virtual ~SoundSystem();
	void Play(const sound_id soundID, const float volume) const override;
	void Pause() const override;
	void Resume() const override;
	void Stop() const override;
	void Load(const char* filePath) override;

};



