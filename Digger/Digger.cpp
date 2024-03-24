#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif



//Managers
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

//GOs + Components
#include "GameObject.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "RotatorComponent.h"

//Commands
#include "MoveCommand.h"


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);


	//==================================
	//STEPS FOR A GAMEOBJECT:
	//1. init ptr
	//2. build up GO
	//3. add to scene
	//==================================



	//===== BACKGROUND =====
	//1. init ptr
	dae::GameObject* GOBackground = new dae::GameObject{};
	//2. build up GO
	GOBackground->AddComponent<dae::TransformComponent>(0.f, 0.f);
	GOBackground->AddComponent<dae::TextureComponent>("Background.tga", false);
	//3. add to scene
	scene.Add(GOBackground);


	//===== ROTATORS =====

	////1. init ptr
	//dae::GameObject* GOCenterPoint = new dae::GameObject{};
	////2. build up GO
	//GOCenterPoint->AddComponent<dae::TransformComponent>(200.f, 200.f);
	////GOCenterPoint->AddComponent<dae::TextureComponent>("Dwarf_Fortress_Icon_Scaled.png", true);
	////3. add to scene
	//scene.Add(GOCenterPoint);

//1. init ptr
	dae::GameObject* GOOne = new dae::GameObject{};
	//2. build up GO
	GOOne->AddComponent<dae::TransformComponent>(200.f, 100.f);
	GOOne->AddComponent<dae::TextureComponent>("Dwarf_Fortress_Icon_Scaled.png", true);
	//GORotatorOne->AddComponent<dae::RotatorComponent>(100.f, 90.f, true, 0.f);
	//GORotatorOne->SetParent(GOCenterPoint, false);
	//3. add to scene
	scene.Add(GOOne);






	dae::GameObject* GOTwo = new dae::GameObject{};
	//2. build up GO
	GOTwo->AddComponent<dae::TransformComponent>(400.f, 100.f);
	GOTwo->AddComponent<dae::TextureComponent>("Dwarf_Fortress_Icon_Scaled.png", true);
	//GORotatorTwo->AddComponent<dae::RotatorComponent>(100.f, 90.f, false, 0.f);
	//GORotatorTwo->SetParent(GORotatorOne, false);
	//3. add to scene
	scene.Add(GOTwo);




	//TEXT:

	//======================
	//1. init ptr
	dae::GameObject* GOFPSText = new dae::GameObject{};
	//2. build up GO
	GOFPSText->AddComponent<dae::TransformComponent>(5.f, 5.f);
	GOFPSText->AddComponent<dae::TextureComponent>(false);
	GOFPSText->AddComponent<dae::TextComponent>("FPS", fpsFont);
	GOFPSText->AddComponent<dae::FPSComponent>();
	//3. add to scene
	scene.Add(GOFPSText);

	//======================
	//1. init ptr
	dae::GameObject* GODPadText = new dae::GameObject{};
	//2. build up GO
	GODPadText->AddComponent<dae::TransformComponent>(5.f, 25.f);
	GODPadText->AddComponent<dae::TextureComponent>(false);
	GODPadText->AddComponent<dae::TextComponent>("P1 use D-Pas to move Left object", fpsFont);
	//3. add to scene
	scene.Add(GODPadText);

	//1. init ptr
	dae::GameObject* GOConsoleText = new dae::GameObject{};
	//2. build up GO
	GOConsoleText->AddComponent<dae::TransformComponent>(5.f, 45.f);
	GOConsoleText->AddComponent<dae::TextureComponent>(false);
	GOConsoleText->AddComponent<dae::TextComponent>("P2 use WASD to move right object", fpsFont);
	//3. add to scene
	scene.Add(GOConsoleText);



	//===== BACKGROUND =====




	//CONTROLLER
	//  =====INPUT=====
	auto& input = dae::InputManager::GetInstance();
	const unsigned int controllerOne{ 0 }, controllerTwo{ 1 };
	//==PLAYER ONE
	const float moveSpeed{ 100.f };
	//up
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DpadUp,
		std::make_unique<dae::MoveCommand>(GOOne, moveSpeed,
			glm::vec2{ 0.f, 1.f }), dae::InputType::ISHELD);

	//down
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DPadDown,
		std::make_unique<dae::MoveCommand>(GOOne, moveSpeed,
			glm::vec2{ 0.f, -1.f }), dae::InputType::ISHELD);

	//left
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DpadLeft,
		std::make_unique<dae::MoveCommand>(GOOne, moveSpeed,
			glm::vec2{ -1.f, 0.f }), dae::InputType::ISHELD);

	//right
	input.AddConsoleCommand(controllerOne, dae::Controller::ControllerButton::DPadRight,
		std::make_unique<dae::MoveCommand>(GOOne, moveSpeed,
			glm::vec2{ 1.f, 0.f }), dae::InputType::ISHELD);






	//==PLAYER TWO
	//Up
	input.AddKeyboardCommand(SDL_SCANCODE_UP,
		std::make_unique<dae::MoveCommand>(GOTwo, moveSpeed,
			glm::vec2{ 0.f, 1.f }));
	input.AddConsoleCommand(controllerTwo, dae::Controller::ControllerButton::DpadUp,
		std::make_unique<dae::MoveCommand>(GOTwo, moveSpeed,
			glm::vec2{ 0.f, 1.f }), dae::InputType::ISHELD);

	//Down
	input.AddKeyboardCommand(SDL_SCANCODE_DOWN,
		std::make_unique<dae::MoveCommand>(GOTwo, moveSpeed,
			glm::vec2{ 0.f, -1.f }));
	input.AddConsoleCommand(controllerTwo, dae::Controller::ControllerButton::DPadDown,
		std::make_unique<dae::MoveCommand>(GOTwo, moveSpeed,
			glm::vec2{ 0.f, -1.f }), dae::InputType::ISHELD);

	//left
	input.AddKeyboardCommand(SDL_SCANCODE_LEFT,
		std::make_unique<dae::MoveCommand>(GOTwo, moveSpeed,
			glm::vec2{ -1.f, 0.f }));
	input.AddConsoleCommand(controllerTwo, dae::Controller::ControllerButton::DpadLeft,
		std::make_unique<dae::MoveCommand>(GOTwo, moveSpeed,
			glm::vec2{ -1.f, 0.f }), dae::InputType::ISHELD);

	//right
	input.AddKeyboardCommand(SDL_SCANCODE_RIGHT,
		std::make_unique<dae::MoveCommand>(GOTwo, moveSpeed,
			glm::vec2{ 1.f, 0.f }));
	input.AddConsoleCommand(controllerTwo, dae::Controller::ControllerButton::DPadRight,
		std::make_unique<dae::MoveCommand>(GOTwo, moveSpeed,
			glm::vec2{ 1.f, 0.f }), dae::InputType::ISHELD);


	//old text
	/*go = std::make_shared<dae::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);*/

}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}