#include "SoundSystem.h"
#include <vector>
#include <SDL_mixer.h>
#pragma comment(lib, "SDL2_mixer.lib") //places a library record file
//IMPORTANT: had a problem with the newest lib, so using an older SDL2_Mixer
#include <SDL.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
class SoundSystem::SoundSystemImpl
{
	struct musicLoaderFunctor
	{
		void operator()(std::vector<Mix_Chunk*>& soundEffectsVec)
		{
			while (true)
			{
				//1. create own lock
				std::unique_lock<std::mutex> guard(queueMutex);
				//2. wait for ping
				//queueReadyConditional.wait(guard, StopQueueConditionalFunction);
				queueReadyConditional.wait(guard, [this] {return (!filePathQueue.empty() || stopCycle); });
				//3. check for early out
				if (stopCycle)
				{
					//doesnt work...
					//guard.release();
					//queueMutex.unlock();
					return;
				}//exit
				//4. load sound
				Mix_Chunk* tempChunk = Mix_LoadWAV(filePathQueue.front());
				if (tempChunk != nullptr)
				{
					//5. add sounds
					soundEffectsVec.push_back(tempChunk);
					std::cout << "SoundBank added a sound, Size in SoundSystem is: " << (soundEffectsVec.size() - 1) << ". Added path is: " << filePathQueue.front() << std::endl;
				}
				else
				{
					std::cout << "soundPath " << filePathQueue.front() << " is invalid." << std::endl;
				}
				filePathQueue.pop();
			}
		}
		bool StopQueueConditionalFunction() const { return (!filePathQueue.empty() || stopCycle); };
		std::condition_variable queueReadyConditional{};
		std::mutex queueMutex{};
		std::queue<const char*> filePathQueue{};
		bool stopCycle{false};
		void AddAndNotify(const char* filePath)
		{
			{
				std::lock_guard<std::mutex> guard(queueMutex);
				filePathQueue.push(filePath);
			}
			queueReadyConditional.notify_all();
		}
		void NotifyQuit()
		{
			stopCycle = true;
			queueReadyConditional.notify_all();
		}
	};

private:
	std::vector<Mix_Chunk*>m_SoundEffects; //needs to be initialized before the thread and functor as its passed
	//todo: make map with filePaths so that they can be remembered as loaded or not
	std::unique_ptr<musicLoaderFunctor> m_SoundEffectLoadingFunctorPtr;
	std::jthread m_SoundEffectsThread;
public:
	SoundSystemImpl()
		: m_SoundEffects{}
		, m_SoundEffectLoadingFunctorPtr{ std::make_unique<musicLoaderFunctor>()}
		, m_SoundEffectsThread{std::ref(*m_SoundEffectLoadingFunctorPtr), std::ref(m_SoundEffects)}
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
			//NOTICED IT ENTERED HERE IF NO AUIO DEVICE IS ACTIVE
			std::cout << "COMMON MISTAKE: It could be that you have no activated audio output device, make sure to have at least 1 set of speakers, headphones or audio device enabled" << std::endl;
			exit(-1);
			//standard error logging and exiting application, 
		}
	};

	~SoundSystemImpl()
	{
		m_SoundEffectLoadingFunctorPtr->NotifyQuit();
		if (m_SoundEffectsThread.joinable())m_SoundEffectsThread.join();
		//delete m_SoundEffectLoadingFunctorPtr;
		//todo: alex question: how do i fix mutex being busy here?
		for (auto& se : m_SoundEffects)
		{
			Mix_FreeChunk(se);
			//delete se;//don't fully know if this is needed
		}
		m_SoundEffects.clear();
		Mix_Quit();
		
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

		m_SoundEffectLoadingFunctorPtr->AddAndNotify(filePath);

		/*Mix_Chunk* tempChunk = Mix_LoadWAV(filePath);
		if (tempChunk != nullptr)
		{
			m_SoundEffects.push_back(tempChunk);
			std::cout << "SoundBank added a sound, Size in SoundSystem is: " << (m_SoundEffects.size() - 1) << ". Added path is: " << filePath << std::endl;
		}*/
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
