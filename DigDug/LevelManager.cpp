#include "LevelManager.h"
#include "PointComponent.h"

void digdug::LevelManager::LoadLevel(std::string filename)
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 21);
	auto& scene = SceneManager::GetInstance().GetCurrentScene();
	auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + "Levels/" + filename;
	auto levelname = filename.substr(0, filename.size() - 4);
	auto& level = SceneManager::GetInstance().CreateScene(levelname);

	//auto groundLevelOne = std::make_unique<GameObject>();
	//groundLevelOne->AddComponent<CollisionComponent>();
	//auto groundLevelTwo = std::make_unique<GameObject>();
	//groundLevelTwo->AddComponent<CollisionComponent>();
	//auto groundLevelThree = std::make_unique<GameObject>();
	//groundLevelThree->AddComponent<CollisionComponent>();
	//auto groundLevelFour = std::make_unique<GameObject>();

	auto sharedScoringObject = std::make_shared<GameObject>();
	auto sharedLivesObject = std::make_shared<GameObject>();
	if (scene.HasNoUIObjects())
	{
		sharedScoringObject->AddComponent<TextComponent>()->SetFont(font);
		sharedScoringObject->GetComponent<TextComponent>()->SetText("0");
		sharedScoringObject->AddComponent<PointComponent>()->Initialize();
		sharedScoringObject->SetLocalPosition({ 100.f,20.f,0.f });
		scene.AddUI(sharedScoringObject);

		sharedLivesObject->AddComponent<LivesDisplay>()->Initialize();
		sharedLivesObject->SetLocalPosition({ 0.f,460.f,0.f });
		scene.AddUI(sharedLivesObject);
	}
	else
	{
		auto objects = scene.MoveOverUI(level);
		for (const auto& object : objects)
		{
			if (object->GetComponent<PointComponent>() != nullptr)
			{
				sharedScoringObject = object;
				continue;

			}
			if (object->GetComponent<LivesDisplay>() != nullptr)
			{
				sharedLivesObject = object;
				break;

			}

		}

	}

	SceneManager::GetInstance().ChangeSceneTo(levelname);
	bool empty = level.isSceneEmpty();
	if (empty)
	{


		std::fstream txtFile(fullPath, std::ios_base::in);
		auto pooka = std::make_unique<GameObject>();
		auto fygar = std::make_unique<GameObject>();
		auto tile = std::make_unique<GameObject>();
		auto firstSprite = std::make_unique<GameObject>();

		tile->AddComponent<TileComponent>()->Initialize();
		auto tileSize = tile->GetComponent<SpriteComponent>()->GetSpriteSize();
		tile->MarkForDeletion(true);
		level.Add(std::move(tile));

		auto& input = InputManager::GetInstance();
		auto& collisions = CollisionManager::GetInstance();
		auto& enemies = EnemyManager::GetInstance();
		auto scoringObject = std::make_unique<GameObject>();
		scoringObject->AddComponent<TextComponent>()->SetFont(font);
		scoringObject->GetComponent<TextComponent>()->SetText(std::to_string(ReadHighScoreFromFile()));
		scoringObject->SetLocalPosition({ 300.f,20.f,0.f });
		level.Add(std::move(scoringObject));

		scoringObject = std::make_unique<GameObject>();
		scoringObject->AddComponent<TextComponent>()->SetFont(font);
		scoringObject->GetComponent<TextComponent>()->SetText("HIGHSCORE");
		scoringObject->SetLocalPosition({ 250.f,0.f,0.f });
		level.Add(std::move(scoringObject));

		scoringObject = std::make_unique<GameObject>();
		scoringObject->AddComponent<TextComponent>()->SetFont(font);
		scoringObject->GetComponent<TextComponent>()->SetText("1P SCORE");
		scoringObject->SetLocalPosition({ 80.f,0.f,0.f });
		level.Add(std::move(scoringObject));

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
				IncreaseRow(currentXTile, currentYTile, maxTileColumn);
				break;

			case levelType::tile:

				tile = std::make_unique<GameObject>();
				if (currentYTile % 3 == 0 && currentYTile != 0 && currentYTile != 12 && currentXTile == 0)
				{
					++currentTileType;
				}
				tile->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });
				tile->AddComponent<TileComponent>()->Initialize();
				tile->GetComponent<TileComponent>()->SetSandType(tileTypes[currentTileType]);

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);

				collisions.AddCollision(tile->GetComponent<CollisionComponent>());
				level.Add(std::move(tile));
				break;

			case levelType::player:

				firstSprite->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });
				firstSprite->AddComponent<DigDugComponent>()->Initialize();
				firstSprite->GetComponent<HealthComponent>()->GetSubject()->AddObserver(sharedLivesObject->GetComponent<LivesDisplay>());
				CreateInputSolo(firstSprite);
				input.AddKeyboardController(firstSprite.get());

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);

				level.Add(std::move(firstSprite));

				break;

			case levelType::pooka:
				pooka = std::make_unique<GameObject>();
				pooka->AddComponent<PookaComponent>()->Initialize();

				pooka->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);
				pooka->GetComponent<PookaComponent>()->GetSubject()->AddObserver(sharedScoringObject->GetComponent<PointComponent>());
				collisions.AddCollision(pooka->GetComponent<CollisionComponent>());
				enemies.AddEnemies(pooka->GetComponent<PookaComponent>());
				level.Add(std::move(pooka));
				break;

			case  levelType::fyger:
				fygar = std::make_unique<GameObject>();
				fygar->AddComponent<FygarsComponent>()->Initialize();

				fygar->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);
				fygar->GetComponent<FygarsComponent>()->GetSubject()->AddObserver(sharedScoringObject->GetComponent<PointComponent>());

				collisions.AddCollision(fygar->GetComponent<CollisionComponent>());
				enemies.AddEnemies(fygar->GetComponent<FygarsComponent>());
				level.Add(std::move(fygar));
				break;

			case  levelType::rock:
				auto rock = std::make_unique<GameObject>();

				tile = std::make_unique<GameObject>();
				tile->AddComponent<TileComponent>()->Initialize();
				if (currentYTile % 3 == 0
					&& currentYTile != 0 && currentYTile != 12
					&& currentXTile == 0)
				{
					++currentTileType;
				}
				tile->GetComponent<TileComponent>()->SetSandType(tileTypes[currentTileType]);
				tile->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });
				rock->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });
				rock->AddComponent<RockComponent>()->Initialize();

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);

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

void digdug::LevelManager::LoadCoopLevel(std::string filename)
{
	auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + "Levels/" + filename;

	auto& level = SceneManager::GetInstance().CreateScene(filename.substr(0, filename.size() - 4));

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

			IncreaseRow(currentXTile, currentYTile, maxTileColumn);

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

			IncreaseRow(currentXTile, currentYTile, maxTileColumn);

			collisions.AddCollision(tile->GetComponent<CollisionComponent>());
			level.Add(std::move(tile));
			break;

		case levelType::playerOne:

			firstSprite->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
			firstSprite->AddComponent<HealthComponent>()->Initialize();
			firstSprite->AddComponent<DigDugComponent>()->Initialize();

			CreateInputSolo(firstSprite);
			input.AddKeyboardController(firstSprite.get());

			IncreaseRow(currentXTile, currentYTile, maxTileColumn);

			level.Add(std::move(firstSprite));
			break;
		case levelType::playerTwo:

			secondSprite->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });
			secondSprite->AddComponent<HealthComponent>()->Initialize();
			secondSprite->AddComponent<DigDugComponent>()->Initialize();

			CreateInputSolo(secondSprite);
			input.AddKeyboardController(secondSprite.get());

			IncreaseRow(currentXTile, currentYTile, maxTileColumn);

			level.Add(std::move(secondSprite));
			break;

		case levelType::pooka:

			pooka = std::make_unique<GameObject>();
			pooka->AddComponent<PookaComponent>()->Initialize();

			pooka->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });

			IncreaseRow(currentXTile, currentYTile, maxTileColumn);

			collisions.AddCollision(pooka->GetComponent<CollisionComponent>());
			level.Add(std::move(pooka));
			break;

		case  levelType::fyger:

			fygar = std::make_unique<GameObject>();
			fygar->AddComponent<FygarsComponent>()->Initialize();

			fygar->SetLocalPosition({ (tileSize.width * currentXTile),(currentYTile * tileSize.height) + startingBottom,0.f });

			IncreaseRow(currentXTile, currentYTile, maxTileColumn);

			collisions.AddCollision(fygar->GetComponent<CollisionComponent>());
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

			IncreaseRow(currentXTile, currentYTile, maxTileColumn);

			collisions.AddCollision(rock->GetComponent<CollisionComponent>());
			collisions.AddCollision(tile->GetComponent<CollisionComponent>());
			level.Add(std::move(tile));
			level.Add(std::move(rock));

			break;
		}
	}
}

void digdug::LevelManager::CreateInputSolo(std::unique_ptr<GameObject>& firstSprite)
{
	firstSprite->AddComponent<InputComponent>();

	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new MoveCommand(firstSprite.get(), Direction::up), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_A, new MoveCommand(firstSprite.get(), Direction::left), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new MoveCommand(firstSprite.get(), Direction::down), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_D, new MoveCommand(firstSprite.get(), Direction::right), InputType::Press);

	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_F, new PumpCommand(firstSprite.get(), "Sounds/Sound/PumpSound.wav", 4), InputType::Down);
	firstSprite->GetComponent<InputComponent>()->SetMovementSpeed(120.f);
}
void digdug::LevelManager::CreateInput_Coop(std::unique_ptr<GameObject>& firstSprite, std::unique_ptr<GameObject>& secondSprite)
{
	firstSprite->AddComponent<InputComponent>();
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new MoveCommand(firstSprite.get(), Direction::up), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_A, new MoveCommand(firstSprite.get(), Direction::left), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new MoveCommand(firstSprite.get(), Direction::down), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_D, new MoveCommand(firstSprite.get(), Direction::right), InputType::Press);
	//	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_R, new KillCommand(firstSprite.get()), InputType::Down);
	firstSprite->GetComponent<InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_F, new PumpCommand(firstSprite.get(), "Sounds/Sound/PumpSound.wav", 4), InputType::Down);
	firstSprite->GetComponent<InputComponent>()->SetMovementSpeed(120.f);

	secondSprite->AddComponent<InputComponent>();

	firstSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadDown, new MoveCommand(firstSprite.get(), Direction::up), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadUp, new MoveCommand(firstSprite.get(), Direction::left), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadLeft, new MoveCommand(firstSprite.get(), Direction::down), InputType::Press);
	firstSprite->GetComponent<InputComponent>()->BindControllerCommand(ControllerButton::DPadRight, new MoveCommand(firstSprite.get(), Direction::right), InputType::Press);

	secondSprite->GetComponent<InputComponent>()->SetMovementSpeed(240.f);
}

int digdug::LevelManager::ReadHighScoreFromFile()
{
	auto highScore = 0;
	auto fullpath = dae::ResourceManager::GetInstance().GetDataPath() + "Score/HighScore.txt";
	std::fstream txtFile;
	txtFile.open(fullpath, std::ios_base::in);
	txtFile >> highScore;
	txtFile.close();
	return highScore;
}

void digdug::LevelManager::SaveHighScoreInFile(int highScore)
{
	auto currentHighscore = ReadHighScoreFromFile();
	auto fullpath = dae::ResourceManager::GetInstance().GetDataPath() + "Score/HighScore.txt";
	std::fstream txtFile;
	txtFile.open(fullpath, std::ios_base::out);
	if (highScore > currentHighscore)
	{
		txtFile.clear();
		txtFile << highScore;
	}
	txtFile.close();
}

void digdug::LevelManager::IncreaseRow(int& x, int& y, int maxTileColumn)
{
	++x;
	if (x == maxTileColumn)
	{
		++y;
		x = 0;
	}
}
