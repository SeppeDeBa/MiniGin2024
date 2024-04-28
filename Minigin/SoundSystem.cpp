#include "SoundSystem.h"
#include <vector>
#include <SDL_mixer.h>
#pragma comment(lib, "SDL2_mixer.lib") //places a library record file
//IMPORTANT: had a problem with the newest lib, so using an older SDL2_Mixer
#include <SDL.h>
#include <iostream>
#include <thread>
#include <mutex>

class SoundSystem::SoundSystemImpl
{
	struct musicLoaderFunctor
	{
		void operator()
	};

private:
	std::vector<Mix_Chunk*>m_SoundEffects{};
	std::mutex m_SoundEffectsVectorMutex{};
	std::vector<std::jthread*> m_SoundEffectsThreads{};
public:
	SoundSystemImpl()
	{
		SDL_Init(SDL_INIT_AUDIO);

		//Defaults found on the Youtube channel of Code, Tech, and Tutorials, aswell as gneeral initialisation mixed with the GL_Mixer documentation
		int audio_rate = 22050;
		Uint16 audio_format = AUDIO_S16SYS;
		int audio_channels = 2;
		int audio_buffers = 4096;

		if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not init audio: %s", Mix_GetError());
			exit(-1);
			//standard error logging and exiting application, 
		}
	};
	~SoundSystemImpl()
	{
		for (auto& se : m_SoundEffects)
		{
			Mix_FreeChunk(se);
			delete se;//don't fully know if this is needed
		}
		m_SoundEffects.clear();
	};

	void Play(const sound_id soundId, const float volume) const {
		if (soundId > m_SoundEffects.size() - 1)
		{
			std::cout << "id is higher than the amount of existing sounds" << std::endl;
		}
		else
		{
			m_SoundEffects[soundId]->volume = static_cast<Uint8>(volume); //autoconversion should be fine...
			Mix_PlayChannel(-1, m_SoundEffects[soundId], 0);
			std::cout << "Played sound ID: " << soundId << std::endl;
		}
	};
	void Pause() const {

	}

	void Resume() const {

	}

	void Stop() const {

	}

	void Load(const char* filePath) {
		Mix_Chunk* tempChunk = Mix_LoadWAV(filePath);
		if (tempChunk != nullptr)
		{
			m_SoundEffects.push_back(tempChunk);
			std::cout << "SoundBank added a sound, Size in SoundSystem is: " << (m_SoundEffects.size() - 1) << ". Added path is: " << filePath << std::endl;
		}
	}
};


SoundSystem::SoundSystem()
{
	m_pImpl = std::make_unique<SoundSystemImpl>();
}

SoundSystem::~SoundSystem()
{
}

void SoundSystem::Play(const sound_id soundID, const float volume) const
{
	m_pImpl->Play(soundID, volume);
}

void SoundSystem::Pause() const
{
	m_pImpl->Pause();
}

void SoundSystem::Resume() const
{
	m_pImpl->Resume();
}

void SoundSystem::Stop() const
{
	m_pImpl->Stop();
}

void SoundSystem::Load(const char* filePath)
{
	m_pImpl->Load(filePath);
}
