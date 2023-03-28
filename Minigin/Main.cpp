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
#include "FPSComponent.h"
#include "RotationComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "InputManager.h"
using namespace dae;
void load()
{
	auto& input = InputManager::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto go = std::make_unique<GameObject>();
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->SetTexture("background.tga");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition(glm::vec3(216.f, 180.f, 0.f));
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->SetTexture("logo.tga");
//	go->GetComponent<RenderComponent>()->SetPosition(216.f, 180.f);
	scene.Add(std::move(go));

	go = std::make_unique<GameObject>();
	go->SetLocalPosition(glm::vec3(80.f, 20.f, 0.f));
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	go->AddComponent<TextComponent>()->SetText("Programming 4 Assignment");
	//go->GetComponent<TextComponent>()->SetPosition(80.f, 20.f);
	go->GetComponent<TextComponent>()->SetFont(font);
	scene.Add(std::move(go));


	go = std::make_unique<GameObject>();
	go->SetLocalPosition(glm::vec3(0.f, 420.f, 0.f));
	go->AddComponent<TextComponent>()->SetText("FPS: ");
	go->GetComponent<TextComponent>()->SetFont(font);
//	go->GetComponent<TextComponent>()->SetPosition(0.f, 420.f);
	go->AddComponent<FPSComponent>()->Initialize();
	scene.Add(std::move(go));

	auto firstSprite = std::make_unique<GameObject>();
	//auto secondSprite = new GameObject();
	auto secondSprite = std::make_unique<GameObject>();


	firstSprite->SetLocalPosition(glm::vec3(290.f, 300.f, 0.f));
	firstSprite->AddComponent<RenderComponent>()->SetTexture("singleSprite.png");
	//firstSprite->AddComponent<SpriteComponent>(); 
	firstSprite->AddComponent<InputComponent>();


	firstSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadDown, new MoveUpDownCommand(firstSprite.get(), 1), InputType::Press);

	firstSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadUp, new MoveUpDownCommand(firstSprite.get(),-1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadLeft, new MoveLeftRightCommand(firstSprite.get(),-1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadRight, new MoveLeftRightCommand(firstSprite.get(),1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->SetMovementSpeed(120.f);
	input.AddController(firstSprite.get(), 0);

	//const auto spriteRenderer = firstSprite->GetComponent<SpriteComponent>();
	//spriteRenderer->AddAnimationStrips("deathAnimation.png", 4, 1, 5, 1, "DeathAnimation");
	//spriteRenderer->SetAnimationByName("DeathAnimation");
	
	secondSprite->SetLocalPosition(glm::vec3(250.f, 300.f, 0.f));
	secondSprite->AddComponent<RenderComponent>()->SetTexture("singleSpriteTwo.png");
	secondSprite->AddComponent<InputComponent>();

	secondSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDLK_s, new MoveUpDownCommand(secondSprite.get(), 1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDLK_w, new MoveUpDownCommand(secondSprite.get(), -1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDLK_a, new MoveLeftRightCommand(secondSprite.get(), -1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDLK_d, new MoveLeftRightCommand(secondSprite.get(), 1), InputType::Press);

	secondSprite->GetComponent<InputComponent>()->SetMovementSpeed(240.f);
	input.AddKeyboardController(secondSprite.get());
	//secondSprite->SetParent(firstSprite.get(), false); 

	scene.Add(std::move(firstSprite));
	scene.Add(std:: move(secondSprite));

	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}