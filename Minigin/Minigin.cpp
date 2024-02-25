#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"

#include <chrono>
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	const float fixed_timestep{ 1.f/60.f };

	// todo: this update loop could use some work.
	bool doContinue = true;
	auto prev_cycle_timestamp{ std::chrono::high_resolution_clock::now() }; //save curr cycle time

	float lag{ 0.f };
	const std::chrono::seconds seconds_per_frame{ 1 / 60 };


	std::chrono::milliseconds ms_per_frame{std::chrono::duration_cast<std::chrono::milliseconds>(seconds_per_frame)};
	while (doContinue)
	{
		//timeData and set cycle to current
		const auto current_time{ std::chrono::high_resolution_clock::now() };
		const float deltaTime{ std::chrono::duration<float>(current_time - prev_cycle_timestamp).count()};
		prev_cycle_timestamp = std::chrono::high_resolution_clock::now();
		lag += deltaTime;

		//input
		doContinue = input.ProcessInput();
		
		

		while(lag >= fixed_timestep)
		{
			//physics update
			lag -= fixed_timestep;
		}

		sceneManager.Update(deltaTime);
		renderer.Render();


		const auto sleeping_time{ current_time + ms_per_frame - std::chrono::high_resolution_clock::now() };

		std::this_thread::sleep_for(sleeping_time);
	}
}
