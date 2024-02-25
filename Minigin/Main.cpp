#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

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
	GOBackground->AddComponent<dae::TextureComponent>("Background.tga");
	//3. add to scene
	scene.Add(GOBackground);
	//======================
	//1. init ptr
	dae::GameObject* GOFPSText = new dae::GameObject{};
	//2. build up GO
	GOFPSText->AddComponent<dae::Transform>(5.f, 5.f);
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