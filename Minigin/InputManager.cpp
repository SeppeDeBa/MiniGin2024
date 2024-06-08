#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include <SDL.h>
#include "InputManager.h"
#include "../3rdParty/imgui-1.90.4/imgui_impl_sdl2.h"
#include <iostream>
#include "Command.h"


//TODO: Pimpl away XInput and maybe windows in InputManager
bool dae::InputManager::ProcessInput(float deltaTime)
{
	//1. update controllers to check input
	for (auto& controller : m_VectorControllers)
	{
		//update
		controller->Update();

		for (auto command = m_controllerCommands.begin(); command != m_controllerCommands.end(); ++command)
		{
			if (command->first.first != controller->GetControlledIdx()) continue; //go to next controller if it's not this one
			switch (command->second.second)
			{
			case InputType::ISDOWN:
				if (controller->IsDown(command->first.second))
				{
					command->second.first->Execute(deltaTime);
				}
				break;
			case InputType::ISHELD:
				if (controller->IsPressed(command->first.second))
				{
					command->second.first->Execute(deltaTime);
				}
				break;
			case InputType::ISUP:
				if (controller->IsUp(command->first.second))
				{
					command->second.first->Execute(deltaTime);
				}
				break;

			default:
				std::cout << "Hit default in ProcessInput() in InputManager, Should not happen!" << std::endl;
				break;
			}
		}
	}


	//2. Do Keyboard Input
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	for (auto command = m_keyboardCommands.begin(); command != m_keyboardCommands.end(); ++command)
	{
		if (keystate[command->first])
		{
			command->second->Execute(deltaTime);
		}
	}


	SDL_Event e;
	//press down
	while (SDL_PollEvent(&e))
	{
		//check keyboard imput
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{

			break;
		}
		if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_i:
				break;
			}
			break;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}

		//IMGUI input
		ImGui_ImplSDL2_ProcessEvent(&e);
		// etc...
	}
	return true;
	//return m_pImpl->ProcessInput();
}

dae::InputManager::InputManager()
//: m_pImpl {std::make_unique<InputManagerImpl>()}
{
	//is it okay to initialise the pimpl in the member init list? 

	std::cout << "Initialising InputManager: " << std::endl;
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			m_VectorControllers.push_back(std::make_unique<Controller>(i));
		}
		else
		{
			std::cout << "There is no controller with idx: " << i << std::endl;
		}
	}
}

void dae::InputManager::AddConsoleCommand(unsigned int controllerIndex, Controller::ControllerButton button, std::unique_ptr<Command>&& command, InputType typeOfInput)
{
	if (controllerIndex <= m_VectorControllers.size() - 1)
	{
		ControllerKey controllerKey = std::make_pair(controllerIndex, button);
		m_controllerCommands.insert(std::make_pair(controllerKey, (std::make_pair(std::move(command), typeOfInput))));
	}
	else
	{
		std::cout << "Button assigned to idx" << controllerIndex << ", index does not exist!" << std::endl;
	}
}

void dae::InputManager::ClearConsoleCommandsForIndex(unsigned int controllerIndex)
{
	for (auto it = m_controllerCommands.begin(); it != m_controllerCommands.end(); ) {
		if (it->first.first == controllerIndex) {
			it = m_controllerCommands.erase(it);
		}
		else {
			++it;
		}
	}
}

void dae::InputManager::AddKeyboardCommand(SDL_Scancode keyboardButton, std::unique_ptr<dae::Command>&& command)
{
	m_keyboardCommands.insert(std::make_pair(keyboardButton, std::move(command)));
}
