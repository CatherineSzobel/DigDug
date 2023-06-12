#include "LevelManager.h"
#include "PointComponent.h"

void digdug::LevelManager::LoadLevel(std::string filename)
{
	auto& scene = dae::SceneManager::GetInstance().GetCurrentScene();
	auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + "Levels/Single/" + filename;
	auto levelname = filename.substr(0, filename.size() - 4);
	auto& level = dae::SceneManager::GetInstance().CreateScene(levelname);
	auto& collisions = dae::CollisionManager::GetInstance();
	


	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 21);

	auto sharedScoringObject = std::make_shared<dae::GameObject>();
	auto sharedLivesObject = std::make_shared<dae::GameObject>();
	if (scene.HasOneUIObject())
	{

		sharedScoringObject->AddComponent<dae::TextComponent>()->SetFont(font);
		sharedScoringObject->GetComponent<dae::TextComponent>()->SetText("0");
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

	dae::SceneManager::GetInstance().ChangeSceneTo(levelname);
	bool empty = level.isSceneEmpty();
	if (empty)
	{
		std::fstream txtFile(fullPath, std::ios_base::in);
		auto pooka = std::make_unique<dae::GameObject>();
		auto fygar = std::make_unique<dae::GameObject>();
		auto tile = std::make_unique<dae::GameObject>();
		auto firstSprite = std::make_unique<dae::GameObject>();

		tile->AddComponent<TileComponent>()->Initialize();
		auto tileSize = tile->GetComponent<dae::SpriteComponent>()->GetSpriteSize();
		tile->MarkForDeletion(true);
		level.Add(std::move(tile));


		auto& enemies = EnemyManager::GetInstance();
		auto scoringObject = std::make_unique<dae::GameObject>();
		scoringObject->AddComponent<dae::TextComponent>()->SetFont(font);
		scoringObject->GetComponent<dae::TextComponent>()->SetText(std::to_string(ReadHighScoreFromFile()));
		scoringObject->SetLocalPosition({ 300.f,20.f,0.f });
		level.Add(std::move(scoringObject));

		scoringObject = std::make_unique<dae::GameObject>();
		scoringObject->AddComponent<dae::TextComponent>()->SetFont(font);
		scoringObject->GetComponent<dae::TextComponent>()->SetText("HIGHSCORE");
		scoringObject->SetLocalPosition({ 250.f,0.f,0.f });
		level.Add(std::move(scoringObject));

		scoringObject = std::make_unique<dae::GameObject>();
		scoringObject->AddComponent<dae::TextComponent>()->SetFont(font);
		scoringObject->GetComponent<dae::TextComponent>()->SetText("1P SCORE");
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

				tile = std::make_unique<dae::GameObject>();
				if (currentYTile % 3 == 0 && currentYTile != 0 && currentYTile != 12 && currentXTile == 0)
				{
					++currentTileType;
				}
				tile->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });
				tile->AddComponent<TileComponent>()->Initialize();
				tile->GetComponent<TileComponent>()->SetSandType(tileTypes[currentTileType]);

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);

				collisions.AddCollision(tile->GetComponent<dae::CollisionComponent>());
				level.Add(std::move(tile));
				break;

			case levelType::player:

				firstSprite->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });
				firstSprite->AddComponent<DigDugComponent>()->Initialize();
				firstSprite->GetComponent<HealthComponent>()->GetSubject()->AddObserver(sharedLivesObject->GetComponent<LivesDisplay>());
				CreateInputSolo(firstSprite, both);


				IncreaseRow(currentXTile, currentYTile, maxTileColumn);

				level.Add(std::move(firstSprite));

				break;

			case levelType::pooka:
				pooka = std::make_unique<dae::GameObject>();
				pooka->AddComponent<PookaComponent>()->Initialize();

				pooka->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);
				pooka->GetComponent<PookaComponent>()->GetSubject()->AddObserver(sharedScoringObject->GetComponent<PointComponent>());
				collisions.AddCollision(pooka->GetComponent<dae::CollisionComponent>());
				enemies.AddEnemies(pooka->GetComponent<PookaComponent>());
				level.Add(std::move(pooka));
				break;

			case  levelType::fyger:
				fygar = std::make_unique<dae::GameObject>();
				fygar->AddComponent<FygarsComponent>()->Initialize();

				fygar->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);
				fygar->GetComponent<FygarsComponent>()->GetSubject()->AddObserver(sharedScoringObject->GetComponent<PointComponent>());

				collisions.AddCollision(fygar->GetComponent<dae::CollisionComponent>());
				enemies.AddEnemies(fygar->GetComponent<FygarsComponent>());
				level.Add(std::move(fygar));
				break;

			case  levelType::rock:
				auto rock = std::make_unique<dae::GameObject>();

				tile = std::make_unique<dae::GameObject>();
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

				collisions.AddCollision(rock->GetComponent<dae::CollisionComponent>());
				collisions.AddCollision(tile->GetComponent<dae::CollisionComponent>());
				level.Add(std::move(tile));
				level.Add(std::move(rock));

				break;
			}
		}
	}
	EnemyManager::GetInstance().SetEnemiesActive();
	dae::CollisionManager::GetInstance().SetCollisionsActive();
}

void digdug::LevelManager::LoadCoopLevel(std::string filename)
{
	auto& scene = dae::SceneManager::GetInstance().GetCurrentScene();
	auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + "Levels/CoOp/" + filename;
	auto levelname = filename.substr(0, filename.size() - 4);
	auto& level = dae::SceneManager::GetInstance().CreateScene(levelname);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 21);

	auto sharedScoringObject = std::make_shared<dae::GameObject>();
	auto sharedLivesObject = std::make_shared<dae::GameObject>();
	auto sharedLivesObjectTwo = std::make_shared<dae::GameObject>();
	if (scene.HasOneUIObject())
	{
		sharedScoringObject->AddComponent<dae::TextComponent>()->SetFont(font);
		sharedScoringObject->GetComponent<dae::TextComponent>()->SetText("0");
		sharedScoringObject->AddComponent<PointComponent>()->Initialize();
		sharedScoringObject->SetLocalPosition({ 100.f,20.f,0.f });
		scene.AddUI(sharedScoringObject);

		sharedLivesObject->AddComponent<LivesDisplay>()->Initialize();
		sharedLivesObject->SetLocalPosition({ 0.f,460.f,0.f });
		scene.AddUI(sharedLivesObject);

		sharedLivesObjectTwo->AddComponent<LivesDisplay>()->Initialize();
		sharedLivesObjectTwo->SetLocalPosition({ 300.f,460.f,0.f });
		scene.AddUI(sharedLivesObjectTwo);
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

	dae::SceneManager::GetInstance().ChangeSceneTo(levelname);
	bool empty = level.isSceneEmpty();
	if (empty)
	{
		auto scoringObject = std::make_unique<dae::GameObject>();
		scoringObject->AddComponent<dae::TextComponent>()->SetFont(font);
		scoringObject->GetComponent<dae::TextComponent>()->SetText(std::to_string(ReadHighScoreFromFile()));
		scoringObject->SetLocalPosition({ 300.f,20.f,0.f });
		level.Add(std::move(scoringObject));

		scoringObject = std::make_unique<dae::GameObject>();
		scoringObject->AddComponent<dae::TextComponent>()->SetFont(font);
		scoringObject->GetComponent<dae::TextComponent>()->SetText("HIGHSCORE");
		scoringObject->SetLocalPosition({ 250.f,0.f,0.f });
		level.Add(std::move(scoringObject));

		scoringObject = std::make_unique<dae::GameObject>();
		scoringObject->AddComponent<dae::TextComponent>()->SetFont(font);
		scoringObject->GetComponent<dae::TextComponent>()->SetText("1P SCORE");
		scoringObject->SetLocalPosition({ 80.f,0.f,0.f });
		level.Add(std::move(scoringObject));

		std::fstream txtFile(fullPath, std::ios_base::in);
		auto pooka = std::make_unique<dae::GameObject>();
		auto fygar = std::make_unique<dae::GameObject>();
		auto firstSprite = std::make_unique<dae::GameObject>();
		auto secondSprite = std::make_unique<dae::GameObject>();
		auto tile = std::make_unique<dae::GameObject>();

		tile->AddComponent<TileComponent>()->Initialize();
		auto tileSize = tile->GetComponent<dae::SpriteComponent>()->GetSpriteSize();
		tile->MarkForDeletion(true);
		level.Add(std::move(tile));

		auto& collisions = dae::CollisionManager::GetInstance();
		auto& enemies = EnemyManager::GetInstance();

		const int maxTileColumn = 20;
		int currentXTile = 0, currentYTile = 0, currentTileType = 0;
		const float startingBottom = 100.f;
		enum class levelType
		{
			empty = 0,
			tile = 1,
			player = 2,
			secondPlayer = 3,
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

				tile = std::make_unique<dae::GameObject>();
				if (currentYTile % 3 == 0 && currentYTile != 0 && currentYTile != 12 && currentXTile == 0)
				{
					++currentTileType;
				}
				tile->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });
				tile->AddComponent<TileComponent>()->Initialize();
				tile->GetComponent<TileComponent>()->SetSandType(tileTypes[currentTileType]);

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);

				collisions.AddCollision(tile->GetComponent<dae::CollisionComponent>());
				level.Add(std::move(tile));
				break;

			case levelType::player:

				firstSprite->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });
				firstSprite->AddComponent<DigDugComponent>()->Initialize();
				firstSprite->GetComponent<HealthComponent>()->GetSubject()->AddObserver(sharedLivesObject->GetComponent<LivesDisplay>());
				CreateInputSolo(firstSprite, keyboard);

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);

				level.Add(std::move(firstSprite));

				break;
			case levelType::secondPlayer:

				secondSprite->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });
				secondSprite->AddComponent<DigDugComponent>()->Initialize();
				secondSprite->GetComponent<HealthComponent>()->GetSubject()->AddObserver(sharedLivesObjectTwo->GetComponent<LivesDisplay>());
				CreateInputSolo(secondSprite, controller);


				IncreaseRow(currentXTile, currentYTile, maxTileColumn);

				level.Add(std::move(secondSprite));

				break;

			case levelType::pooka:
				pooka = std::make_unique<dae::GameObject>();
				pooka->AddComponent<PookaComponent>()->Initialize();

				pooka->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);
				pooka->GetComponent<PookaComponent>()->GetSubject()->AddObserver(sharedScoringObject->GetComponent<PointComponent>());
				pooka->GetComponent<PookaComponent>()->GetSubject()->AddObserver(sharedScoringObject->GetComponent<PointComponent>());

				collisions.AddCollision(pooka->GetComponent<dae::CollisionComponent>());
				enemies.AddEnemies(pooka->GetComponent<PookaComponent>());
				level.Add(std::move(pooka));
				break;

			case  levelType::fyger:
				fygar = std::make_unique<dae::GameObject>();
				fygar->AddComponent<FygarsComponent>()->Initialize();

				fygar->SetLocalPosition({ (tileSize.x * currentXTile),(currentYTile * tileSize.y) + startingBottom,0.f });

				IncreaseRow(currentXTile, currentYTile, maxTileColumn);
				fygar->GetComponent<FygarsComponent>()->GetSubject()->AddObserver(sharedScoringObject->GetComponent<PointComponent>());
				fygar->GetComponent<FygarsComponent>()->GetSubject()->AddObserver(sharedScoringObject->GetComponent<PointComponent>());

				collisions.AddCollision(fygar->GetComponent<dae::CollisionComponent>());
				enemies.AddEnemies(fygar->GetComponent<FygarsComponent>());
				level.Add(std::move(fygar));
				break;

			case  levelType::rock:
				auto rock = std::make_unique<dae::GameObject>();

				tile = std::make_unique<dae::GameObject>();
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

				collisions.AddCollision(rock->GetComponent<dae::CollisionComponent>());
				collisions.AddCollision(tile->GetComponent<dae::CollisionComponent>());
				level.Add(std::move(tile));
				level.Add(std::move(rock));

				break;
			}
		}
		
	}
	
	EnemyManager::GetInstance().SetEnemiesActive();
	dae::CollisionManager::GetInstance().SetCollisionsActive();
}

void digdug::LevelManager::CreateInputSolo(std::unique_ptr<dae::GameObject>& sprite, ControllerType type)
{
	auto& input = dae::InputManager::GetInstance();
	sprite->AddComponent<dae::InputComponent>();
	switch (type)
	{
	case digdug::both:

		sprite->GetComponent<dae::InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new MoveCommand(sprite.get(), Direction::up), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_A, new MoveCommand(sprite.get(), Direction::left), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new MoveCommand(sprite.get(), Direction::down), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_D, new MoveCommand(sprite.get(), Direction::right), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_F, new PumpCommand(sprite.get(), "Sounds/Sound/PumpSound.wav", 4), dae::InputType::Down);

		sprite->GetComponent<dae::InputComponent>()->BindControllerCommand(dae::ControllerButton::DPadDown, new MoveCommand(sprite.get(), Direction::down), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindControllerCommand(dae::ControllerButton::DPadUp, new MoveCommand(sprite.get(), Direction::up), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindControllerCommand(dae::ControllerButton::DPadLeft, new MoveCommand(sprite.get(), Direction::left), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindControllerCommand(dae::ControllerButton::DPadRight, new MoveCommand(sprite.get(), Direction::right), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindControllerCommand(dae::ControllerButton::ButtonA, new PumpCommand(sprite.get(), "Sounds/Sound/PumpSound.wav", 4), dae::InputType::Down);

		sprite->GetComponent<dae::InputComponent>()->SetMovementSpeed(120.f);

		input.AddKeyboardController(sprite.get());
		input.AddController(sprite.get(), 0);

		break;
	case digdug::controller:

		sprite->GetComponent<dae::InputComponent>()->BindControllerCommand(dae::ControllerButton::DPadDown, new MoveCommand(sprite.get(), Direction::down), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindControllerCommand(dae::ControllerButton::DPadUp, new MoveCommand(sprite.get(), Direction::up), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindControllerCommand(dae::ControllerButton::DPadLeft, new MoveCommand(sprite.get(), Direction::left), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindControllerCommand(dae::ControllerButton::DPadRight, new MoveCommand(sprite.get(), Direction::right), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindControllerCommand(dae::ControllerButton::ButtonA, new PumpCommand(sprite.get(), "Sounds/Sound/PumpSound.wav", 4), dae::InputType::Down);
		
		sprite->GetComponent<dae::InputComponent>()->SetMovementSpeed(120.f);
		input.AddController(sprite.get(), 0);

		break;
	case digdug::keyboard:

		sprite->GetComponent<dae::InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_W, new MoveCommand(sprite.get(), Direction::up), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_A, new MoveCommand(sprite.get(), Direction::left), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_S, new MoveCommand(sprite.get(), Direction::down), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_D, new MoveCommand(sprite.get(), Direction::right), dae::InputType::Press);
		sprite->GetComponent<dae::InputComponent>()->BindKeyboardCommand(SDL_SCANCODE_F, new PumpCommand(sprite.get(), "Sounds/Sound/PumpSound.wav", 4), dae::InputType::Down);
		
		sprite->GetComponent<dae::InputComponent>()->SetMovementSpeed(120.f);
		input.AddKeyboardController(sprite.get());

		break;
	}
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
