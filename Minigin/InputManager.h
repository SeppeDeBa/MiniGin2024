#pragma once
#include <memory>
#include "Singleton.h"
#include <utility>
#include "Controller.h"
#include "Command.h"
#include <map>
#include <vector>
#include <mutex>
namespace dae
{
	enum class InputType
	{
		ISDOWN,
		ISUP,
		ISHELD
	};
	class InputManager final : public Singleton<InputManager>
	{

		//class InputManagerImpl;
		//std::unique_ptr<InputManagerImpl> m_pImpl;

		using ControllerKey = std::pair<unsigned int, dae::Controller::ControllerButton>;
		using ControllerCommandsMap = std::map<ControllerKey, std::pair<std::unique_ptr<Command>, InputType>>;
		ControllerCommandsMap m_controllerCommands{};
		ControllerCommandsMap m_controllerCommandsBackBuffer{}; //double buffer swaps at end of Process Input;
		using KeyboardMap = std::map < SDL_Scancode, std::unique_ptr<Command>>;
		KeyboardMap m_keyboardCommands{};


		std::vector<std::unique_ptr<Controller>> m_VectorControllers{};



		std::unique_ptr<Command> arrowUp;


	public:
		bool ProcessInput(float deltaTime);
		InputManager();
		void AddConsoleCommand(unsigned int controllerIndex, Controller::ControllerButton button, std::unique_ptr<dae::Command>&& command, InputType typeOfInput);
		void ClearConsoleCommandsForIndex(unsigned int controllerIndex);
		void ClearConsoleCommandsForIndex(std::vector<unsigned int>& indicesToRemove);

		void AddKeyboardCommand(SDL_Scancode keyboardButton, std::unique_ptr<dae::Command>&& command);

		std::vector<unsigned int> m_RemoveCommandsFromIndexVec{};
		//	void SetUpArrow(Command* command) { arrowUp = std::make_unique<Command>(command);};
	};
}
