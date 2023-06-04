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
#include "Enemies/PookaComponent.h"
#include "Enemies/EnemyManager.h"
using namespace dae;
using namespace digdug;
void CreateInputSolo(std::unique_ptr<GameObject>& firstSprite);
void CreateInput_Coop(std::unique_ptr<GameObject>& firstSprite, std::unique_ptr<GameObject>& secondSprite);
void SaveAllCollision(std::vector<Rectf>& m_pCollision, std::unique_ptr<GameObject>& go);
void CreateLevels();
void CreateLevelFromTxtFile(std::string filename,Scene& scene);
void load()
{

	CreateLevels();
	servicelocator::get_sound_system().PlayMusic("Sounds/Music/Theme.mp3", 1, true);
	auto& input = InputManager::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().GetCurrentScene();
	auto& collisions = CollisionManager::GetInstance();
	input.BindKeyboardCommand(SDL_SCANCODE_F1, new NextSceneCommand(), InputType::Down);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 21);
	auto go = std::make_unique<GameObject>();
	go->SetLocalPosition(glm::vec3(0.f, 0.f, 0.f));
	go->AddComponent<TextComponent>()->SetText("FPS: ");
	go->GetComponent<TextComponent>()->SetFont(font);
	go->AddComponent<FPSComponent>()->Initialize();
	scene.Add(std::move(go));

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

void CreateInputSolo(std::unique_ptr<GameObject>& )
{
	//firstSprite->AddComponent<InputComponent>();
	//firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new MoveUpDownCommand(firstSprite.get(), 1), InputType::Press);
	//firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new MoveUpDownCommand(firstSprite.get(), -1), InputType::Press);
	//firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_A, new MoveLeftRightCommand(firstSprite.get(), -1), InputType::Press);
	//firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_D, new MoveLeftRightCommand(firstSprite.get(), 1), InputType::Press);
	//firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_F, new PumpCommand(firstSprite.get(), "Sounds/Sound/PumpSound.wav", 4), InputType::Down);
	//firstSprite->GetComponent<InputComponent>()->SetMovementSpeed(120.f);
}

void CreateInput_Coop(std::unique_ptr<GameObject>& , std::unique_ptr<GameObject>& )
{
	//firstSprite->AddComponent<InputComponent>();
	//firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new MoveUpDownCommand(firstSprite.get(), 1), InputType::Press);
	//firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new MoveUpDownCommand(firstSprite.get(), -1), InputType::Press);
	//firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_A, new MoveLeftRightCommand(firstSprite.get(), -1), InputType::Press);
	//firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_D, new MoveLeftRightCommand(firstSprite.get(), 1), InputType::Press);
	////	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_R, new KillCommand(firstSprite.get()), InputType::Down);
	//firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_F, new PumpCommand(firstSprite.get(), "Sounds/Sound/PumpSound.wav", 4), InputType::Down);
	//firstSprite->GetComponent<InputComponent>()->SetMovementSpeed(120.f);

	//secondSprite->AddComponent<InputComponent>();
	//secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadDown, new MoveUpDownCommand(secondSprite.get(), 1), InputType::Press);
	//secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadUp, new MoveUpDownCommand(secondSprite.get(), -1), InputType::Press);
	//secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadLeft, new MoveLeftRightCommand(secondSprite.get(), -1), InputType::Press);
	//secondSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadRight, new MoveLeftRightCommand(secondSprite.get(), 1), InputType::Press);

	//secondSprite->GetComponent<InputComponent>()->SetMovementSpeed(240.f);
}

void SaveAllCollision(std::vector<Rectf>& m_pCollision, std::unique_ptr<GameObject>& go)
{
	m_pCollision.emplace_back(go->GetComponent<CollisionComponent>()->GetCollision());
}

void CreateLevelFromTxtFile(std::string , Scene& )
{

	//CollisionManager::GetInstance().ResetCollision();
	//std::fstream txtFile(filename, std::ios_base::in);
	//
	//auto pooka = std::make_unique<GameObject>();
	//auto fygar = std::make_unique<GameObject>();
	//auto tile = std::make_unique<GameObject>();
	//auto firstSprite = std::make_unique<GameObject>();
	//
	//tile->AddComponent<TileComponent>()->Initialize();
	//tile->GetComponent<TileComponent>()->SetSandType(TileType::YellowSand);
	//auto tileSize = tile->GetComponent<SpriteComponent>()->GetCurrentSpriteSize();
	//tile->SetLocalPosition({ 0.f,100.f,0.f });
	//level.Add(std::move(tile));

	//auto& input = InputManager::GetInstance();
	//auto& collisions = CollisionManager::GetInstance();

	//const int maxTileColumn = 20;
	//int currentXTile = 0, currentYTile = 0, currentTileType = 0;
	//const float startingBottom = 100.f;
	//enum class levelType
	//{
	//	empty = 0,
	//	tile = 1,
	//	player = 2,
	//	pooka = 3,
	//	fyger = 4,
	//	rock = 5
	//};
	//int value = 0;
	//levelType type = levelType::empty;
	//std::vector<TileType> tileTypes = { TileType::YellowSand,TileType::OrangeSand,TileType::BrownSand,TileType::RedSand };

	//while (txtFile >> value)
	//{
	//	type = (levelType)value;
	//	switch (type)
	//	{
	//	case levelType::empty:
	//		printf(" 0 ");
	//		++currentXTile;
	//		if (currentXTile == maxTileColumn)
	//		{
	//			printf("\n");
	//			++currentYTile;
	//			currentXTile = 0;
	//		}
	//		break;

	//	case levelType::tile:

	//		printf(" 1 ");
	//		tile = std::make_unique<GameObject>();
	//		tile->AddComponent<TileComponent>()->Initialize();
	//		if (currentYTile % 3 == 0 && currentYTile != 0 && currentYTile != 12 && currentXTile == 0)
	//		{
	//			++currentTileType;
	//		}
	//		tile->GetComponent<TileComponent>()->SetSandType(tileTypes[currentTileType]);
	//		tile->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
	//		++currentXTile;
	//		if (currentXTile == maxTileColumn)
	//		{
	//			printf("\n");
	//			++currentYTile;
	//			currentXTile = 0;
	//		}
	//		collisions.AddCollision(tile->GetComponent<CollisionComponent>());
	//		level.Add(std::move(tile));
	//		break;

	//	case levelType::player:
	//		printf(" 2 ");

	//		firstSprite->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
	//		firstSprite->AddComponent<HealthComponent>()->Initialize();
	//		firstSprite->AddComponent<DigDugComponent>()->Initialize();

	//		CreateInputSolo(firstSprite);
	//		input.AddKeyboardController(firstSprite.get());
	//		++currentXTile;
	//		if (currentXTile == maxTileColumn)
	//		{
	//			printf("\n");
	//			++currentYTile;
	//			currentXTile = 0;
	//		}
	//		level.Add(std::move(firstSprite));
	//		break;

	//	case levelType::pooka:
	//		printf(" 3 ");
	//		pooka = std::make_unique<GameObject>();
	//		pooka->AddComponent<PookaComponent>()->Initialize();

	//		pooka->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });

	//		++currentXTile;
	//		if (currentXTile == maxTileColumn)
	//		{
	//			printf("\n");
	//			++currentYTile;
	//			currentXTile = 0;
	//		}
	//		collisions.AddCollision(pooka->GetComponent<CollisionComponent>());
	//		level.Add(std::move(pooka));
	//		break;

	//	case  levelType::fyger:
	//		printf(" 4 ");
	//		fygar = std::make_unique<GameObject>();
	//		fygar->AddComponent<FygarsComponent>()->Initialize();

	//		fygar->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });

	//		++currentXTile;
	//		if (currentXTile == maxTileColumn)
	//		{
	//			printf("\n");
	//			++currentYTile;
	//			currentXTile = 0;
	//		}
	//		collisions.AddCollision(fygar->GetComponent<CollisionComponent>());
	//		level.Add(std::move(fygar));
	//		break;

	//	case  levelType::rock:
	//		printf(" 5 ");
	//		auto rock = std::make_unique<GameObject>();
	//		rock->AddComponent<RockComponent>()->Initialize();
	//		auto rockSize = rock->GetComponent<SpriteComponent>()->GetCurrentSpriteSize();

	//		tile = std::make_unique<GameObject>();
	//		tile->AddComponent<TileComponent>()->Initialize();
	//		if (currentYTile % 3 == 0
	//			&& currentYTile != 0 && currentYTile != 12
	//			&& currentXTile == 0)
	//		{
	//			++currentTileType;
	//		}
	//		tile->GetComponent<TileComponent>()->SetSandType(tileTypes[currentTileType]);
	//		tile->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
	//		rock->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
	//		++currentXTile;
	//		if (currentXTile == maxTileColumn)
	//		{
	//			printf("\n");
	//			++currentYTile;
	//			currentXTile = 0;
	//		}
	//		collisions.AddCollision(rock->GetComponent<CollisionComponent>());
	//		collisions.AddCollision(tile->GetComponent<CollisionComponent>());
	//		level.Add(std::move(tile));
	//		level.Add(std::move(rock));

	//		break;
	//	}
	//}

}

void CreateLevels()
{
	auto& firstLevel = dae::SceneManager::GetInstance().CreateScene("firstLevel");
	auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + "Levels/level1.txt";
	LevelManager::GetInstance().LoadLevel(fullPath, firstLevel);

	//auto& secondLevel = dae::SceneManager::GetInstance().CreateScene("secondLevel");
	//fullPath = dae::ResourceManager::GetInstance().GetDataPath() + "Levels/level2.txt";
	//LevelManager::GetInstance().LoadLevel(fullPath, secondLevel);
}
