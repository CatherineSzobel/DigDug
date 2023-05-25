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
#include "LivesDisplay.h"
#include "TileComponent.h"
#include "RockComponent.h"
#include "Enemies/PookaComponent.h"
#include "Enemies/FygarsComponent.h"
#include "Enemies/EnemyManager.h"
using namespace dae;
void MakePlayerAnimation(std::vector<Sprite*>& listOfAnimation);
void CreateInputSolo(std::unique_ptr<GameObject>& firstSprite);
void CreateInput_Coop(std::unique_ptr<GameObject>& firstSprite, std::unique_ptr<GameObject>& secondSprite);
void SaveAllCollision(std::vector<Rectf>& m_pCollision, std::unique_ptr<GameObject>& go);
void CreateLevel();
static std::vector<Sprite*>DiggerAnimations;
void load()
{

	MakePlayerAnimation(DiggerAnimations);
	CreateLevel();
	servicelocator::get_sound_system().PlayMusic("Sounds/Music/Theme.mp3", 1, true);
	auto& input = InputManager::GetInstance();
	dae::SceneManager::GetInstance().ChangeSceneTo("firstLevel");
	auto& scene = dae::SceneManager::GetInstance().GetCurrentScene();
	auto& collisions = CollisionManager::GetInstance();

	//auto go = std::make_unique<GameObject>();
	//go->AddComponent<RenderComponent>();
	//go->GetComponent<RenderComponent>()->SetTexture("background.tga");
	//scene.Add(std::move(go));

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 21);
	auto go = std::make_unique<GameObject>();
	go->SetLocalPosition(glm::vec3(0.f, 0.f, 0.f));
	go->AddComponent<TextComponent>()->SetText("FPS: ");
	go->GetComponent<TextComponent>()->SetFont(font);
	go->AddComponent<FPSComponent>()->Initialize();
	scene.Add(std::move(go));




	auto secondSprite = std::make_unique<GameObject>();
	//CreateInput_Coop(firstSprite, secondSprite);
	input.AddController(secondSprite.get(), 0);


	secondSprite->SetLocalPosition(glm::vec3(250.f, 250.f, 0.f));
	secondSprite->AddComponent<SpriteComponent>()->AddAnimationStrips("Sprites/PlayerMoveRight.png", 2, 1, 2, 1 / 2.f, "walkRight");
	secondSprite->GetComponent<SpriteComponent>()->Initialize();
	secondSprite->AddComponent<CollisionComponent>()->CreateCollision(secondSprite->GetComponent<SpriteComponent>()->GetCurrentSpriteSize(), EnemyLayer, true);
	collisions.AddCollision(secondSprite->GetComponent<CollisionComponent>());

	scene.Add(std::move(secondSprite));

	auto UIHUD = std::make_unique<GameObject>();
	UIHUD->AddComponent<LivesDisplay>();
	UIHUD->AddComponent<HealthComponent>();
	UIHUD->GetComponent<HealthComponent>()->Initialize();
	UIHUD->AddComponent<SpriteComponent>()->AddAnimationStrips("Sprites/livesSprite.png", 1, 4, 4.f, 1.f, "lives", true);
	UIHUD->GetComponent<SpriteComponent>()->SetAnimationByName("lives");
	UIHUD->SetLocalPosition({ 0.f,460.f,0.f });
	scene.Add(std::move(UIHUD));

	auto undergroundBoundary = std::make_unique<GameObject>();
	undergroundBoundary->SetLocalPosition({ 0.f,100.f,0.f });
	undergroundBoundary->AddComponent<CollisionComponent>()->CreateCollision(Rectf{ 0.f,0.f,635.f,350.f }, Underground, true);
	collisions.AddCollision(undergroundBoundary->GetComponent<CollisionComponent>());
	scene.Add(std::move(undergroundBoundary));
}

int main(int, char* [])
{

	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}

void MakePlayerAnimation(std::vector<Sprite*>& listOfAnimation)
{
	auto playerScale = 1.5f;
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveLeft.png", 2, 1, 2.f,  1.f / 2.f, "PlayerWalkLeft",false,playerScale });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveRight.png", 2, 1, 2.f,  1.f / 2.f, "PlayerWalkRight",false,playerScale });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveUp.png", 2, 1, 2.f,  1.f / 2.f, "PlayerWalkUp",false,playerScale });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveDown.png", 2, 1, 2.f,  1.f / 2.f, "PlayerWalkDown",false,playerScale });

	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveLeftWithArrow.png", 2, 1, 2.f, 1.f / 2.f, "PlayerMoveLeftWithArrow",false,playerScale });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveRightWithArrow.png", 2, 1, 2.f,  1.f / 2.f, "PlayerMoveRightWithArrow",false,playerScale });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveUpWithArrow.png", 2, 1, 2.f,  1.f / 2.f, "PlayerMoveUpWithArrow",false,playerScale });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerMoveDownWithArrow.png", 2, 1, 2.f,  1.f / 2.f, "PlayerMoveDownWithArrow",false,playerScale });

	listOfAnimation.emplace_back(new Sprite{ "Sprites/deathAnimationPlayer.png", 4, 1, 4.f, 1.f / 3.f, "deathAnimation" ,false,playerScale });


	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerThrowLeft.png",1, 1,1.f, 1.f, "WaterPumpLeft" ,false,playerScale });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerThrowRight.png",1, 1,1.f, 1.f, "WaterPumpRight" ,false,playerScale });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerThrowUp.png",1, 1,1.f, 1.f, "WaterPumpUp",false,playerScale });
	listOfAnimation.emplace_back(new Sprite{ "Sprites/PlayerThrowDown.png",1, 1,1.f, 1.f, "WaterPumpDown",false,playerScale });

}

void CreateInputSolo(std::unique_ptr<GameObject>& firstSprite)
{
	firstSprite->AddComponent<InputComponent>();
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new MoveUpDownCommand(firstSprite.get(), 1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new MoveUpDownCommand(firstSprite.get(), -1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_A, new MoveLeftRightCommand(firstSprite.get(), -1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_D, new MoveLeftRightCommand(firstSprite.get(), 1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_F, new PumpCommand(firstSprite.get(), "Sounds/Sound/PumpSound.wav", 4), InputType::Down);
	firstSprite->GetComponent<InputComponent>()->SetMovementSpeed(120.f);
}

void CreateInput_Coop(std::unique_ptr<GameObject>& firstSprite, std::unique_ptr<GameObject>& secondSprite)
{
	firstSprite->AddComponent<InputComponent>();
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new MoveUpDownCommand(firstSprite.get(), 1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new MoveUpDownCommand(firstSprite.get(), -1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_A, new MoveLeftRightCommand(firstSprite.get(), -1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_D, new MoveLeftRightCommand(firstSprite.get(), 1), InputType::Press);
	//	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_R, new KillCommand(firstSprite.get()), InputType::Down);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_F, new PumpCommand(firstSprite.get(), "Sounds/Sound/PumpSound.wav", 4), InputType::Down);
	firstSprite->GetComponent<InputComponent>()->SetMovementSpeed(120.f);

	secondSprite->AddComponent<InputComponent>();
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadDown, new MoveUpDownCommand(secondSprite.get(), 1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadUp, new MoveUpDownCommand(secondSprite.get(), -1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadLeft, new MoveLeftRightCommand(secondSprite.get(), -1), InputType::Press);
	secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadRight, new MoveLeftRightCommand(secondSprite.get(), 1), InputType::Press);

	secondSprite->GetComponent<InputComponent>()->SetMovementSpeed(240.f);
}

void SaveAllCollision(std::vector<Rectf>& m_pCollision, std::unique_ptr<GameObject>& go)
{
	m_pCollision.emplace_back(go->GetComponent<CollisionComponent>()->GetCollision());
}

void CreateLevel()
{
	auto& firstLevel = dae::SceneManager::GetInstance().CreateScene("firstLevel");
	auto pooka = std::make_unique<GameObject>();
	auto fygar = std::make_unique<GameObject>();
	auto tile = std::make_unique<GameObject>();
	tile->AddComponent<TileComponent>()->Initialize();
	tile->GetComponent<TileComponent>()->SetSandType(TileType::YellowSand);
	auto tileSize = tile->GetComponent<SpriteComponent>()->GetCurrentSpriteSize();

	tile->SetLocalPosition({ 0.f,100.f,0.f });
	firstLevel.Add(std::move(tile));

	//for (int height = 0; height < 11; ++height)
	//{
	//	for (int width = 0; width < 19; ++width)
	//	{
	//		tile = std::make_unique<GameObject>();
	//		tile->AddComponent<TileComponent>()->Initialize();
	//		tile->GetComponent<TileComponent>()->SetSandType(TileType::YellowSand);
	//		tile->SetLocalPosition({ tileSize.width * width,height * tileSize.height + 100.f,0.f });
	//		firstLevel.Add(std::move(tile));
	//	}
	//	tile = std::make_unique<GameObject>();
	//	tile->AddComponent<TileComponent>()->Initialize();
	//	tile->GetComponent<TileComponent>()->SetSandType(TileType::YellowSand);
	//	tile->SetLocalPosition({ 0.f,height * tileSize.height + 100.f,0.f });
	//	firstLevel.Add(std::move(tile));
	//}



	auto& input = InputManager::GetInstance();
	auto& collisions = CollisionManager::GetInstance();
	auto firstSprite = std::make_unique<GameObject>();

	auto fullPath = dae::ResourceManager::GetInstance().GetDataPath();
	std::fstream txtFile(fullPath + "Levels/level1.txt", std::ios_base::in);
	int value = 0;
	const int maxTileColumn = 20;
	//	const int maxTileRow = 12;
	int currentXTile = 0, currentYTile = 0, currentTileType = 0;
	float startingBottom = 100.f;

	std::vector<TileType> tileTypes = { TileType::YellowSand,TileType::OrangeSand,TileType::BrownSand,TileType::RedSand };
	while (txtFile >> value)
	{
		switch (value)
		{
		case 0:
			printf(" 0 ");
			++currentXTile;
			if (currentXTile == maxTileColumn)
			{
				printf("\n");
				++currentYTile;
				currentXTile = 0;
			}
			break;
		case 1:

			printf(" 1 ");
			tile = std::make_unique<GameObject>();
			tile->AddComponent<TileComponent>()->Initialize();
			if (currentYTile % 3 == 0 && currentYTile != 0 && currentYTile != 12 && currentXTile == 0)
			{
				++currentTileType;
			}
			tile->GetComponent<TileComponent>()->SetSandType(tileTypes[currentTileType]);
			tile->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
			++currentXTile;
			if (currentXTile == maxTileColumn)
			{
				printf("\n");
				++currentYTile;
				currentXTile = 0;
			}
			collisions.AddCollision(tile->GetComponent<CollisionComponent>());
			firstLevel.Add(std::move(tile));
			break;
		case 2:
			printf(" 2 ");

			firstSprite->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
			firstSprite->AddComponent<SpriteComponent>();
			firstSprite->AddComponent<HealthComponent>()->Initialize();


			firstSprite->GetComponent<SpriteComponent>()->AddAnimationStrips(DiggerAnimations);
			firstSprite->GetComponent<SpriteComponent>()->SetAnimationByName("PlayerWalkRight");
			auto size = firstSprite->GetComponent<SpriteComponent>()->GetCurrentSpriteSize();
			firstSprite->AddComponent<CollisionComponent>()->CreateCollision(Rectf{ size }, Player, true);
			firstSprite->GetComponent<CollisionComponent>()->SetCollision(true);
			firstSprite->AddComponent<DigDugComponent>()->Initialize();

			CreateInputSolo(firstSprite);
			input.AddKeyboardController(firstSprite.get());
			++currentXTile;
			if (currentXTile == maxTileColumn)
			{
				printf("\n");
				++currentYTile;
				currentXTile = 0;
			}
			collisions.AddCollision(firstSprite->GetComponent<CollisionComponent>());
			firstLevel.Add(std::move(firstSprite));
			break;

		case 3:
			printf(" 3 ");
			pooka = std::make_unique<GameObject>();
			pooka->AddComponent<PookaComponent>()->Initialize();

			pooka->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });

			++currentXTile;
			if (currentXTile == maxTileColumn)
			{
				printf("\n");
				++currentYTile;
				currentXTile = 0;
			}
			collisions.AddCollision(pooka->GetComponent<CollisionComponent>());
			firstLevel.Add(std::move(pooka));
			break;

		case 4:
			printf(" 4 ");
			fygar = std::make_unique<GameObject>();
			fygar->AddComponent<FygarsComponent>()->Initialize();

			fygar->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });

			++currentXTile;
			if (currentXTile == maxTileColumn)
			{
				printf("\n");
				++currentYTile;
				currentXTile = 0;
			}
			collisions.AddCollision(fygar->GetComponent<CollisionComponent>());
			firstLevel.Add(std::move(fygar));
			break;

		case 5:
			printf(" 5 ");
			auto rock = std::make_unique<GameObject>();
			rock->AddComponent<RockComponent>()->Initialize();
			auto rockSize = rock->GetComponent<SpriteComponent>()->GetCurrentSpriteSize();

			tile = std::make_unique<GameObject>();
			tile->AddComponent<TileComponent>()->Initialize();
			if (currentYTile % 3 == 0 
				&& currentYTile != 0 && currentYTile != 12 
				&& currentXTile == 0)
			{
				++currentTileType;
			}
			tile->GetComponent<TileComponent>()->SetSandType(tileTypes[currentTileType]);
			tile->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
			rock->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
			++currentXTile;
			if (currentXTile == maxTileColumn)
			{
				printf("\n");
				++currentYTile;
				currentXTile = 0;
			}
			collisions.AddCollision(rock->GetComponent<CollisionComponent>());
			collisions.AddCollision(tile->GetComponent<CollisionComponent>());
			firstLevel.Add(std::move(tile));
			firstLevel.Add(std::move(rock));

			break;
		}
	}
	//auto& secondLevel = dae::SceneManager::GetInstance().CreateScene("secondLevel");

	//auto& thirdLevel = dae::SceneManager::GetInstance().CreateScene("thirdLevel");

}
