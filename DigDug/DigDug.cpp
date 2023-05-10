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
#include "CollisionComponent.h"
#include "InputManager.h"
using namespace dae;
void MakePlayerAnimation(std::vector<Sprite*>& listOfAnimation);
void CreateInput(std::unique_ptr<GameObject>& firstSprite, std::unique_ptr<GameObject>& secondSprite);
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
	go->SetLocalPosition(glm::vec3(0.f, 0.f, 0.f));
	go->AddComponent<TextComponent>()->SetText("FPS: ");
	go->GetComponent<TextComponent>()->SetFont(font);
	//	go->GetComponent<TextComponent>()->SetPosition(0.f, 420.f);
	go->AddComponent<FPSComponent>()->Initialize();
	scene.Add(std::move(go));

	auto firstSprite = std::make_unique<GameObject>();
	std::vector<Sprite*>DiggerAnimations;
	MakePlayerAnimation(DiggerAnimations);
	//auto spriteRender = firstSprite->GetComponent<SpriteComponent>();
//	firstSprite->AddComponent<CollisionComponent>()->CreateCollision(spriteRender->GetCurrentSpriteSize());

	//auto secondSprite = new GameObject();
	auto secondSprite = std::make_unique<GameObject>();
	//secondSprite->AddComponent<CollisionComponent>();

	firstSprite->SetLocalPosition(glm::vec3(290.f, 300.f, 0.f));
	firstSprite->AddComponent<SpriteComponent>();

	CreateInput(firstSprite, secondSprite);
	input.AddController(secondSprite.get(), 0);
	input.AddKeyboardController(firstSprite.get());

	const auto spriteRenderer = firstSprite->GetComponent<SpriteComponent>();
	spriteRenderer->AddAnimationStrips(DiggerAnimations);
	spriteRenderer->SetAnimationByName("PlayerWalkRight");

	secondSprite->SetLocalPosition(glm::vec3(250.f, 300.f, 0.f));
	secondSprite->AddComponent<RenderComponent>()->SetTexture("Sprites/singleSpriteTwo.png");


	//secondSprite->SetParent(firstSprite.get(), false); 

	auto PlayerOneHealthHUD = std::make_unique<GameObject>();
	PlayerOneHealthHUD->AddComponent<HealthComponent>();
	PlayerOneHealthHUD->AddComponent<TextComponent>()->SetFont(font);
	PlayerOneHealthHUD->GetComponent<TextComponent>()->SetText("Lives: 3");
	PlayerOneHealthHUD->SetLocalPosition({ 0.f,250.f,0.f });

	auto PlayerTwoHealthHUD = std::make_unique<GameObject>();
	PlayerTwoHealthHUD->AddComponent<HealthComponent>();
	PlayerTwoHealthHUD->AddComponent<TextComponent>()->SetFont(font);
	PlayerTwoHealthHUD->GetComponent<TextComponent>()->SetText("Lives: 3");
	PlayerTwoHealthHUD->SetLocalPosition({ 0.f,380.f,0.f });

	auto PlayerOnePointshHUD = std::make_unique<GameObject>();
	PlayerOnePointshHUD->AddComponent<PointsComponent>();

	PlayerOnePointshHUD->AddComponent<TextComponent>()->SetFont(font);
	PlayerOnePointshHUD->GetComponent<TextComponent>()->SetText("Points: 0");
	PlayerOnePointshHUD->SetLocalPosition({ 0.f,200.f,0.f });

	auto PlayerTwoPointsHUD = std::make_unique<GameObject>();
	PlayerTwoPointsHUD->AddComponent<PointsComponent>();
	PlayerTwoPointsHUD->AddComponent<TextComponent>()->SetFont(font);
	PlayerTwoPointsHUD->GetComponent<TextComponent>()->SetText("Points: 0");
	PlayerTwoPointsHUD->SetLocalPosition({ 0.f,320.f,0.f });

	input.BindKeyboardCommand(SDL_SCANCODE_R, new KillCommand(PlayerOneHealthHUD.get()), InputType::Down);
	input.BindKeyboardCommand(SDL_SCANCODE_E, new KillCommand(PlayerTwoHealthHUD.get()), InputType::Down);

	input.BindKeyboardCommand(SDL_SCANCODE_G, new IncreasePointsCommand(PlayerOnePointshHUD.get()), InputType::Down);
	input.BindKeyboardCommand(SDL_SCANCODE_H, new IncreasePointsCommand(PlayerTwoPointsHUD.get()), InputType::Down);
	std::string path = "Sounds/Music/Theme.mp3";
	std::string soundPath = "button.wav";
	input.BindKeyboardCommand(SDL_SCANCODE_0, new PlayMusicCommand(path, 5), InputType::Down);
	input.BindKeyboardCommand(SDL_SCANCODE_1, new PlaySoundCommand(soundPath, 5), InputType::Down);

	scene.Add(std::move(firstSprite));
	scene.Add(std::move(secondSprite));

	scene.Add(std::move(PlayerOneHealthHUD));
	scene.Add(std::move(PlayerTwoHealthHUD));
	scene.Add(std::move(PlayerOnePointshHUD));
	scene.Add(std::move(PlayerTwoPointsHUD));
}

int main(int, char* []) {

	//if (!SteamAPI_Init())
	//{
	//	std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
	//	return 1;
	//}
	//else
	//	std::cout << "Successfully initialized steam." << std::endl;


	dae::Minigin engine("../Data/");
	engine.Run(load);

	//SteamAPI_Shutdown();
	return 0;
}

void MakePlayerAnimation(std::vector<Sprite*>& listOfAnimation)
{
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveLeft.png", 2, 1, 2.f, 1.f, "PlayerWalkLeft" });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveRight.png", 2, 1, 2.f, 1.f, "PlayerWalkRight" });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveUp.png", 2, 1, 2.f, 1.f, "PlayerWalkUp" });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveDown.png", 2, 1, 2.f, 1.f, "PlayerWalkDown" });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/walkAnimationWithArrow.png", 2, 1, 2.f, 1.f, "walkingWithArrow" });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/underGroundWalkAnimationOne.png", 2, 1, 2.f, 1.f, "undergroundWalkingWithArrow" });

}

void CreateInput(std::unique_ptr<GameObject>& firstSprite, std::unique_ptr<GameObject>& secondSprite)
{
	firstSprite->AddComponent<InputComponent>();
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new MoveUpDownCommand(firstSprite.get(), 1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new MoveUpDownCommand(firstSprite.get(), -1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_A, new MoveLeftRightCommand(firstSprite.get(), -1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_D, new MoveLeftRightCommand(firstSprite.get(), 1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->SetMovementSpeed(120.f);

	secondSprite->AddComponent<InputComponent>();
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadDown, new MoveUpDownCommand(secondSprite.get(), 1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadUp, new MoveUpDownCommand(secondSprite.get(), -1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadLeft, new MoveLeftRightCommand(secondSprite.get(), -1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadRight, new MoveLeftRightCommand(secondSprite.get(), 1), InputType::Press);

	secondSprite->GetComponent<InputComponent>()->SetMovementSpeed(240.f);
}
