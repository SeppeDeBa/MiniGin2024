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

//GOs + Components
#include "GameObject.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "RotatorComponent.h"

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

	//1. init ptr
	dae::GameObject* GOCenterPoint = new dae::GameObject{};
	//2. build up GO
	GOCenterPoint->AddComponent<dae::TransformComponent>(200.f, 200.f);
	//GOCenterPoint->AddComponent<dae::TextureComponent>("Dwarf_Fortress_Icon_Scaled.png", true);
	//3. add to scene
	scene.Add(GOCenterPoint);

//1. init ptr
	dae::GameObject* GORotatorOne = new dae::GameObject{};
	//2. build up GO
	GORotatorOne->AddComponent<dae::TransformComponent>(0.f, 0.f);
	GORotatorOne->AddComponent<dae::TextureComponent>("Dwarf_Fortress_Icon_Scaled.png", true);
	GORotatorOne->AddComponent<dae::RotatorComponent>(100.f, 90.f, true, 0.f);
	GORotatorOne->SetParent(GOCenterPoint, false);
	//3. add to scene
	scene.Add(GORotatorOne);






	dae::GameObject* GORotatorTwo = new dae::GameObject{};
	//2. build up GO
	GORotatorTwo->AddComponent<dae::TransformComponent>(0.f, 0.f);
	GORotatorTwo->AddComponent<dae::TextureComponent>("Dwarf_Fortress_Icon_Scaled.png", true);
	GORotatorTwo->AddComponent<dae::RotatorComponent>(100.f, 90.f, false, 0.f);
	GORotatorTwo->SetParent(GORotatorOne, false);
	//3. add to scene
	scene.Add(GORotatorTwo);




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

	//===== BACKGROUND =====







	//old text
	/*go = std::make_shared<dae::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);*/

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}