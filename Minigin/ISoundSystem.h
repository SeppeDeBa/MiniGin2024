#pragma once
using sound_id = unsigned short;
class ISoundSystem
{
public:
	virtual ~ISoundSystem() = default;
	virtual void Play(const sound_id soundID, const float volume) const = 0;
	virtual void Pause() const = 0;
	virtual void Resume() const = 0;
	virtual void Stop() const = 0;
	virtual void Load(const char* filePath) = 0; //changed from string to const char* since SDL_Mixer uses it by default
};

