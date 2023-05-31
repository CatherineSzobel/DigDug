#include "LevelManager.h"

void dae::LevelManager::LoadLevel(std::string filename, Scene& level)
{
	CollisionManager::GetInstance().ResetCollision();
	bool empty = level.isSceneEmpty();
	if (empty)
	{


		std::fstream txtFile(filename, std::ios_base::in);
		auto pooka = std::make_unique<GameObject>();
		auto fygar = std::make_unique<GameObject>();
		auto tile = std::make_unique<GameObject>();
		auto firstSprite = std::make_unique<GameObject>();

		tile->AddComponent<TileComponent>()->Initialize();
		tile->GetComponent<TileComponent>()->SetSandType(TileType::YellowSand);
		auto tileSize = tile->GetComponent<SpriteComponent>()->GetCurrentSpriteSize();
		tile->SetLocalPosition({ 0.f,100.f,0.f });
		level.Add(std::move(tile));

		auto& input = InputManager::GetInstance();
		auto& collisions = CollisionManager::GetInstance();
		auto& enemies = EnemyManager::GetInstance();

		const int maxTileColumn = 20;
		int currentXTile = 0, currentYTile = 0, currentTileType = 0;
		const float startingBottom = 100.f;
		enum class levelType
		{
			empty = 0,
			tile = 1,
			player = 2,
			pooka = 3,
			fyger = 4,
			rock = 5
		};
		int value = 0;
		levelType type = levelType::empty;
		std::vector<TileType> tileTypes = { TileType::YellowSand,TileType::OrangeSand,TileType::BrownSand,TileType::RedSand };

		while (txtFile >> value)
		{
			type = (levelType)value;
			switch (type)
			{
			case levelType::empty:
				++currentXTile;
				if (currentXTile == maxTileColumn)
				{
					++currentYTile;
					currentXTile = 0;
				}
				break;

			case levelType::tile:

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
					++currentYTile;
					currentXTile = 0;
				}
				collisions.AddCollision(tile->GetComponent<CollisionComponent>());
				level.Add(std::move(tile));
				break;

			case levelType::player:

				firstSprite->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
				firstSprite->AddComponent<HealthComponent>()->Initialize();
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
				level.Add(std::move(firstSprite));
				break;

			case levelType::pooka:
				pooka = std::make_unique<GameObject>();
				pooka->AddComponent<PookaComponent>()->Initialize();

				pooka->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });

				++currentXTile;
				if (currentXTile == maxTileColumn)
				{
					++currentYTile;
					currentXTile = 0;
				}
				collisions.AddCollision(pooka->GetComponent<CollisionComponent>());
				enemies.AddEnemies(pooka->GetComponent<PookaComponent>());
				level.Add(std::move(pooka));
				break;

			case  levelType::fyger:
				fygar = std::make_unique<GameObject>();
				fygar->AddComponent<FygarsComponent>()->Initialize();

				fygar->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });

				++currentXTile;
				if (currentXTile == maxTileColumn)
				{
					++currentYTile;
					currentXTile = 0;
				}
				collisions.AddCollision(fygar->GetComponent<CollisionComponent>());
				enemies.AddEnemies(fygar->GetComponent<FygarsComponent>());
				level.Add(std::move(fygar));
				break;

			case  levelType::rock:
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
					++currentYTile;
					currentXTile = 0;
				}
				collisions.AddCollision(rock->GetComponent<CollisionComponent>());
				collisions.AddCollision(tile->GetComponent<CollisionComponent>());
				level.Add(std::move(tile));
				level.Add(std::move(rock));

				break;
			}
		}
	}
	EnemyManager::GetInstance().SetEnemiesActive();
	CollisionManager::GetInstance().SetCollisionsActive();
}

void dae::LevelManager::LoadCoopLevel(std::string filename, Scene& level)
{
	CollisionManager::GetInstance().ResetCollision();
	std::fstream txtFile(filename, std::ios_base::in);

	auto pooka = std::make_unique<GameObject>();
	auto fygar = std::make_unique<GameObject>();
	auto tile = std::make_unique<GameObject>();
	auto firstSprite = std::make_unique<GameObject>();
	auto secondSprite = std::make_unique<GameObject>();

	tile->AddComponent<TileComponent>()->Initialize();
	tile->GetComponent<TileComponent>()->SetSandType(TileType::YellowSand);
	auto tileSize = tile->GetComponent<SpriteComponent>()->GetCurrentSpriteSize();
	tile->SetLocalPosition({ 0.f,100.f,0.f });
	level.Add(std::move(tile));

	auto& input = InputManager::GetInstance();
	auto& collisions = CollisionManager::GetInstance();

	const int maxTileColumn = 20;
	int currentXTile = 0, currentYTile = 0, currentTileType = 0;
	const float startingBottom = 100.f;
	enum class levelType
	{
		empty = 0,
		tile = 1,
		playerOne = 2,
		playerTwo = 3,
		pooka = 4,
		fyger = 5,
		rock = 6
	};
	int value = 0;
	levelType type = levelType::empty;
	std::vector<TileType> tileTypes = { TileType::YellowSand,TileType::OrangeSand,TileType::BrownSand,TileType::RedSand };

	while (txtFile >> value)
	{
		type = (levelType)value;
		switch (type)
		{
		case levelType::empty:
			printf(" 0 ");
			++currentXTile;
			if (currentXTile == maxTileColumn)
			{
				printf("\n");
				++currentYTile;
				currentXTile = 0;
			}
			break;

		case levelType::tile:

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
			level.Add(std::move(tile));
			break;

		case levelType::playerOne:
			printf(" 2 ");

			firstSprite->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
			firstSprite->AddComponent<HealthComponent>()->Initialize();
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
			level.Add(std::move(firstSprite));
			break;
		case levelType::playerTwo:
			printf(" 2 ");

			secondSprite->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
			secondSprite->AddComponent<HealthComponent>()->Initialize();
			secondSprite->AddComponent<DigDugComponent>()->Initialize();

			CreateInputSolo(secondSprite);
			input.AddKeyboardController(secondSprite.get());
			++currentXTile;
			if (currentXTile == maxTileColumn)
			{
				printf("\n");
				++currentYTile;
				currentXTile = 0;
			}
			level.Add(std::move(secondSprite));
			break;

		case levelType::pooka:
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
			level.Add(std::move(pooka));
			break;

		case  levelType::fyger:
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
			level.Add(std::move(fygar));
			break;

		case  levelType::rock:
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
			level.Add(std::move(tile));
			level.Add(std::move(rock));

			break;
		}
	}
}

void dae::LevelManager::CreateInputSolo(std::unique_ptr<GameObject>& firstSprite)
{
	firstSprite->AddComponent<InputComponent>();
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new MoveUpDownCommand(firstSprite.get(), 1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new MoveUpDownCommand(firstSprite.get(), -1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_A, new MoveLeftRightCommand(firstSprite.get(), -1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_D, new MoveLeftRightCommand(firstSprite.get(), 1), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_F, new PumpCommand(firstSprite.get(), "Sounds/Sound/PumpSound.wav", 4), InputType::Down);
	firstSprite->GetComponent<InputComponent>()->SetMovementSpeed(120.f);
}

void dae::LevelManager::CreateInput_Coop(std::unique_ptr<GameObject>& firstSprite, std::unique_ptr<GameObject>& secondSprite)
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
