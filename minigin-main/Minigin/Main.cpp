#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "BaseComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Scene.h"
using namespace dae;
void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto go = std::make_shared<GameObject>();
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->SetTexture("logo.tga");
	go->GetComponent<RenderComponent>()->SetPosition(216.f, 180.f);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	go->AddComponent<TextComponent>()->SetText("Programming 4 Assignment");
	go->GetComponent<TextComponent>()->SetPosition(80.f, 20.f);
	go->GetComponent<TextComponent>()->SetFont(font);
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}