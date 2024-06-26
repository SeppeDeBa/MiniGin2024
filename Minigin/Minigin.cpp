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
		g_windowWidth,
		g_windowHeight,
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

	bool doContinue = true;

	const int frameTimeMs{ static_cast<int>(1000.f / m_targetFPS) };
	auto prev_cycle_timestamp{ std::chrono::high_resolution_clock::now() }; //save curr cycle time
	float lag{ 0.f };

	while (doContinue)
	{
		//timeData and set cycle to current
		const auto current_time{ std::chrono::high_resolution_clock::now() }; //curr cycle time
		const float deltaTime{ std::chrono::duration<float>(current_time - prev_cycle_timestamp).count()};
		prev_cycle_timestamp = current_time;
		lag += deltaTime;

		//input
		doContinue = input.ProcessInput(deltaTime);

		//can be used for physics later
		while(lag >= m_fixedTimeStep)
		{
			sceneManager.FixedUpdate();
			lag -= m_fixedTimeStep;
		}

		sceneManager.Update(deltaTime);
		renderer.Render();


		const auto sleeping_time{ current_time + std::chrono::milliseconds(frameTimeMs) - std::chrono::high_resolution_clock::now() };

		std::this_thread::sleep_for(sleeping_time);
	}
}
