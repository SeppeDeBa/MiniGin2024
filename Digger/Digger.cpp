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
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"
//Commands
#include "MoveCommand.h"
#include "DieCommand.h"
#include "ScoreCommand.h"

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
	GOOne->AddComponent<Player>();
	//GORotatorOne->AddComponent<dae::RotatorComponent>(100.f, 90.f, true, 0.f);
	//GORotatorOne->SetParent(GOCenterPoint, false);
	//3. add to scene
	scene.Add(GOOne);

	//SCORES P1
	//1. init ptr
	dae::GameObject* GOScoreP1Text = new dae::GameObject{};
	//2. build up GO
	GOScoreP1Text->AddComponent<dae::TransformComponent>(5.f, 100.f);
	GOScoreP1Text->AddComponent<dae::TextureComponent>(false);
	GOScoreP1Text->AddComponent<dae::TextComponent>("Score:", fpsFont);
	GOScoreP1Text->AddComponent<ScoreDisplayComponent>(GOOne->GetComponent<Player>());
	scene.Add(GOScoreP1Text);

	//Lives P1
	//1. init ptr
	dae::GameObject* GOLivesP1Text = new dae::GameObject{};
	//2. build up GO
	GOLivesP1Text->AddComponent<dae::TransformComponent>(5.f, 125.f);
	GOLivesP1Text->AddComponent<dae::TextureComponent>(false);
	GOLivesP1Text->AddComponent<dae::TextComponent>("Lives:", fpsFont);
	GOLivesP1Text->AddComponent<LivesDisplayComponent>(GOOne->GetComponent<Player>());
	scene.Add(GOLivesP1Text);



	dae::GameObject* GOTwo = new dae::GameObject{};
	//2. build up GO
	GOTwo->AddComponent<dae::TransformComponent>(400.f, 100.f);
	GOTwo->AddComponent<dae::TextureComponent>("Dwarf_Fortress_Icon_Scaled.png", true);
	GOTwo->AddComponent<Player>();
	//GORotatorTwo->AddComponent<dae::RotatorComponent>(100.f, 90.f, false, 0.f);
	//GORotatorTwo->SetParent(GORotatorOne, false);
	//3. add to scene
	scene.Add(GOTwo);

	//SCORES P1
//1. init ptr
	dae::GameObject* GOScoreP2Text = new dae::GameObject{};
	//2. build up GO
	GOScoreP2Text->AddComponent<dae::TransformComponent>(5.f, 150.f);
	GOScoreP2Text->AddComponent<dae::TextureComponent>(false);
	GOScoreP2Text->AddComponent<dae::TextComponent>("Score:", fpsFont);
	GOScoreP2Text->AddComponent<ScoreDisplayComponent>(GOTwo->GetComponent<Player>());
	scene.Add(GOScoreP2Text);

	//Lives P1
	//1. init ptr
	dae::GameObject* GOLivesP2Text = new dae::GameObject{};
	//2. build up GO
	GOLivesP2Text->AddComponent<dae::TransformComponent>(5.f, 175.f);
	GOLivesP2Text->AddComponent<dae::TextureComponent>(false);
	GOLivesP2Text->AddComponent<dae::TextComponent>("Lives:", fpsFont);
	GOLivesP2Text->AddComponent<LivesDisplayComponent>(GOTwo->GetComponent<Player>());
	scene.Add(GOLivesP2Text);


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
	GODPadText->AddComponent<dae::TextComponent>("P1 use D-Pad to move Left object, X to die, Y to get score", fpsFont);
	//3. add to scene
	scene.Add(GODPadText);

	//1. init ptr
	dae::GameObject* GOConsoleText = new dae::GameObject{};
	//2. build up GO
	GOConsoleText->AddComponent<dae::TransformComponent>(5.f, 45.f);
	GOConsoleText->AddComponent<dae::TextureComponent>(false);
	GOConsoleText->AddComponent<dae::TextComponent>("P2 use WASD to move right object, C to get score, X to die", fpsFont);
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

	//die
	input.AddConsoleCommand(controllerOne, Controller::ControllerButton::ButtonX,
		std::make_unique<DieCommand>(GOOne),
		dae::InputType::ISUP);
	//score
	input.AddConsoleCommand(controllerOne, Controller::ControllerButton::ButtonY,
		std::make_unique<ScoreCommand>(GOOne, 100),
		dae::InputType::ISUP);




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
	//die
	input.AddKeyboardCommand(SDL_SCANCODE_C,
		std::make_unique<DieCommand>(GOTwo));

	input.AddConsoleCommand(controllerOne, Controller::ControllerButton::ButtonX,
		std::make_unique<DieCommand>(GOTwo),
		dae::InputType::ISUP);
	//score
	input.AddKeyboardCommand(SDL_SCANCODE_X,
		std::make_unique<ScoreCommand>(GOTwo));
	input.AddConsoleCommand(controllerOne, Controller::ControllerButton::ButtonY,
		std::make_unique<ScoreCommand>(GOTwo, 100),
		dae::InputType::ISUP);

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