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
#include "LivesDisplay.h"
#include "InputManager.h"
using namespace dae;
void MakePlayerAnimation(std::vector<Sprite*>& listOfAnimation);
void AddMusicAndSounds();
void CreateInput(std::unique_ptr<GameObject>& firstSprite, std::unique_ptr<GameObject>& secondSprite);
void load()
{
	AddMusicAndSounds();
	servicelocator::get_sound_system().PlayMusic("Sounds/Music/Theme.mp3",1,true);
	auto& input = InputManager::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_unique<GameObject>();
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->SetTexture("background.tga");
	scene.Add(std::move(go));

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_unique<GameObject>();
	go->SetLocalPosition(glm::vec3(0.f, 0.f, 0.f));
	go->AddComponent<TextComponent>()->SetText("FPS: ");
	go->GetComponent<TextComponent>()->SetFont(font);
	go->AddComponent<FPSComponent>()->Initialize();
	scene.Add(std::move(go));

	auto firstSprite = std::make_unique<GameObject>();
	std::vector<Sprite*>DiggerAnimations;
	MakePlayerAnimation(DiggerAnimations);

	firstSprite->SetLocalPosition(glm::vec3(290.f, 300.f, 0.f));
	firstSprite->AddComponent<SpriteComponent>();
	firstSprite->AddComponent<HealthComponent>()->Initialize();

	const auto spriteRenderer = firstSprite->GetComponent<SpriteComponent>();
	spriteRenderer->AddAnimationStrips(DiggerAnimations);
	spriteRenderer->SetAnimationByName("PlayerWalkRight");
	firstSprite->AddComponent<DigDugComponent>()->Initialize();
	auto spriteRender = firstSprite->GetComponent<SpriteComponent>();
	firstSprite->AddComponent<CollisionComponent>()->CreateCollision(spriteRender->GetCurrentSpriteSize(),true);

	std::cout << "Play sounds with 0 - 4 \n";
	std::cout << "Use the pump command F -> music stops but when u walk it resumes";


	auto secondSprite = std::make_unique<GameObject>();
	CreateInput(firstSprite, secondSprite);
	input.AddController(secondSprite.get(), 0);
	input.AddKeyboardController(firstSprite.get());

	secondSprite->SetLocalPosition(glm::vec3(250.f, 250.f, 0.f));
	secondSprite->AddComponent<SpriteComponent>()->AddAnimationStrips("Sprites/PlayerMoveRight.png",2,1,2,1/2.f,"walkRight");
	secondSprite->GetComponent<SpriteComponent>()->Initialize();
	secondSprite->AddComponent<CollisionComponent>()->CreateCollision(secondSprite->GetComponent<SpriteComponent>()->GetCurrentSpriteSize(),true);

	input.BindKeyboardCommand(SDL_SCANCODE_0, new PlaySoundCommand("button.wav", 5), InputType::Down);
	input.BindKeyboardCommand(SDL_SCANCODE_1, new PlaySoundCommand("Sounds/Sound/DeathSound.wav", 5), InputType::Down);
	input.BindKeyboardCommand(SDL_SCANCODE_2, new PlaySoundCommand("Sounds/Sound/GetHitSound.wav", 5), InputType::Down);
	input.BindKeyboardCommand(SDL_SCANCODE_3, new PlaySoundCommand("Sounds/Sound/PumpSound.wav", 5), InputType::Down);
	input.BindKeyboardCommand(SDL_SCANCODE_4, new PlaySoundCommand("Sounds/Sound/PumpingSound.wav", 5), InputType::Down);

	firstSprite->GetComponent<CollisionComponent>()->SetOtherCollision(secondSprite->GetComponent<CollisionComponent>()->GetCollision());
	scene.Add(std::move(firstSprite));
	scene.Add(std::move(secondSprite));

	auto UIHUD = std::make_unique<GameObject>();
	UIHUD->AddComponent<LivesDisplay>();
	UIHUD->AddComponent<HealthComponent>();
	UIHUD->GetComponent<HealthComponent>()->Initialize();
	UIHUD->AddComponent<SpriteComponent>()->AddAnimationStrips("Sprites/livesSprite.png",1,1,1.f,1.f,"lives");
	UIHUD->GetComponent<SpriteComponent>()->SetAnimationByName("lives");
	UIHUD->SetLocalPosition({0.f,450.f,0.f});
	input.BindKeyboardCommand(SDL_SCANCODE_R, new KillCommand(UIHUD.get()), InputType::Down);

	scene.Add(std::move(UIHUD));
}

int main(int, char* []) 
{

	dae::Minigin engine("../Data/");
	engine.Run(load);
	
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
	listOfAnimation.emplace_back(new Sprite{ "Sprites/deathAnimationPlayer.png", 4, 1, 4.f, 1.f / 3.f, "deathAnimation" });


	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerThrowLeft.png",1, 1,1.f, 1.f, "WaterPumpLeft" });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerThrowRight.png",1, 1,1.f, 1.f, "WaterPumpRight" });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerThrowUp.png",1, 1,1.f, 1.f, "WaterPumpUp" });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerThrowDown.png",1, 1,1.f, 1.f, "WaterPumpDown" });

}

void AddMusicAndSounds()
{
	//auto& ss = servicelocator::get_sound_system();
	//
	//ss.AddAudioClip("Sounds/Sound/PumpSound.wav","PumpSound");
	//ss.AddMusicClip("Sounds/Music/Theme.mp3", "Theme", true);
	//ss.AddMusicClip("Sounds/Music/EntranceSong.mp3", "Entrance", true);
	//
}

void CreateInput(std::unique_ptr<GameObject>& firstSprite, std::unique_ptr<GameObject>& secondSprite)
{
	firstSprite->AddComponent<InputComponent>();
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new MoveUpDownCommand(firstSprite.get(), 1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new MoveUpDownCommand(firstSprite.get(), -1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_A, new MoveLeftRightCommand(firstSprite.get(), -1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_D, new MoveLeftRightCommand(firstSprite.get(), 1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_R, new KillCommand(firstSprite.get()), InputType::Down);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_F, new PumpCommand(firstSprite.get(),"Sounds/Sound/PumpSound.wav", 4), InputType::Down);
	firstSprite->GetComponent<InputComponent>()->SetMovementSpeed(120.f);

	secondSprite->AddComponent<InputComponent>();
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadDown, new MoveUpDownCommand(secondSprite.get(), 1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadUp, new MoveUpDownCommand(secondSprite.get(), -1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadLeft, new MoveLeftRightCommand(secondSprite.get(), -1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadRight, new MoveLeftRightCommand(secondSprite.get(), 1), InputType::Press);

	secondSprite->GetComponent<InputComponent>()->SetMovementSpeed(240.f);
}
