#include <SDL.h>
#include <iostream>
#include <fstream>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "BaseComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "CollisionComponent.h"
#include "LevelManager.h"
#include "LivesDisplay.h"
#include "PointComponent.h"
#include "PookaComponent.h"
#include "EnemyManager.h"
#include "UIComponent.h"
using namespace dae;
using namespace digdug;
void load()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 21);
	auto& input = InputManager::GetInstance();
	auto& firstLevel = dae::SceneManager::GetInstance().CreateScene("level1");
	//auto gameComponent = std::make_shared<GameObject>();
	//gameComponent->AddComponent<UIComponent>()->Initialize();
	//firstLevel.AddUI(gameComponent);

	auto textObject = std::make_unique<GameObject>();
	textObject->SetLocalPosition({ 265.f,300.f,0.f });
	textObject->AddComponent<TextComponent>()->SetFont(font);
	textObject->GetComponent<TextComponent>()->SetText("SinglePlayer");
	firstLevel.Add(std::move(textObject));

	textObject = std::make_unique<GameObject>();
	textObject->SetLocalPosition({ 265.f,330.f,0.f });
	textObject->AddComponent<TextComponent>()->SetFont(font);
	textObject->GetComponent<TextComponent>()->SetText("CoOp");
	firstLevel.Add(std::move(textObject));

	textObject = std::make_unique<GameObject>();
	textObject->SetLocalPosition({ 265.f,200.f,0.f });
	textObject->AddComponent<TextComponent>()->SetFont(font);
	textObject->GetComponent<TextComponent>()->SetText("DIG DUG");
	firstLevel.Add(std::move(textObject));

	auto arrow = std::make_shared<GameObject>();
	arrow->SetLocalPosition({ 220.f,300.f,0 });
	arrow->AddComponent<TextComponent>()->SetFont(font);
	arrow->AddComponent<InputComponent>();
	arrow->AddComponent<UIComponent>()->Initialize();
	arrow->AddComponent<RenderComponent>();
	arrow->GetComponent<RenderComponent>()->SetTexture("Arrow.png");
	arrow->GetComponent<RenderComponent>()->SetScale(25.f);

	arrow->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new HandleUpDownMenuCommand(arrow.get(), Direction::up), InputType::Down);
	arrow->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new HandleUpDownMenuCommand(arrow.get(), Direction::down), InputType::Down);
	input.BindKeyboardCommand(SDL_SCANCODE_RETURN, new HandleMenuCommand(arrow.get()), InputType::Down);

	input.AddKeyboardController(arrow.get());
	firstLevel.AddUI(std::move(arrow));
	input.BindKeyboardCommand(SDL_SCANCODE_F1, new NextSceneCommand(), InputType::Down);
}

int main(int, char* [])
{

	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
