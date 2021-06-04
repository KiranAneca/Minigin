#include "Application.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Scene.h"
#include <memory>
#include <SDL.h>
#include "GameCommands.h"

#include "QBertObserver.h"
#include "CoilyObserver.h"
#include "LivesObserver.h"
#include "SubjectComponent.h"
#include "GameObserver.h"
#include "ScoreComponent.h"
#include "MoveComponent.h"


void Application::InitializeApplication()
{
	std::srand((unsigned int)std::time(NULL));
}

void Application::LoadApllication() const
{
	LoadMainMenu();
	LoadGameSinglePlayer();

	SceneManager::GetInstance().SetSceneActive(true, "GameSceneSingle");
	SceneManager::GetInstance().SetSceneActive(true, "GameSceneMulti");
	SceneManager::GetInstance().SetSceneActive(false, "MainMenu");
}

void Application::CleanupApplication()
{
}

void Application::RunApplication()
{
}

void Application::LoadGameSinglePlayer() const
{
	auto& gameScene = SceneManager::GetInstance().CreateScene("GameSceneSingle");
	auto& gm = GameManager::GetInstance();

	gameScene.SetActive(false);

	gm.SetLives(3);

	// Background
	auto go = std::make_shared<GameObject>();
	auto back = std::make_shared<GameObject>();
	RenderComponent* backgroundSprite = new RenderComponent{ back.get() };
	GameObserver* gameObserver = new GameObserver{ back.get() };
	backgroundSprite->SetTexture("background.jpg");
	back->AddComponent(backgroundSprite);
	back->AddComponent(gameObserver);
	gameScene.Add(back);

	//FPS counter
	go = std::make_shared<GameObject>();
	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	TextRenderComponent* fpsSprite = new TextRenderComponent{ "FPS: ", font2, go.get() };
	TimeComponent* timeComp = new TimeComponent{ go.get() };
	fpsSprite->SetPosition(10, 10);
	go->AddComponent(fpsSprite);
	go->AddComponent(timeComp);
	gameScene.Add(go);

	// Spawning Qbert
	int pyramidHeight = 7;

	auto qbert = std::make_shared<GameObject>();
	RenderComponent* qbertSprite = new RenderComponent{ qbert.get() };
	GridComponent* qbertGrid = new GridComponent{ qbert.get() };
	SubjectComponent* qSubject = new SubjectComponent{ qbert.get() };

	qbertGrid->SetGrid(0, pyramidHeight - 1);
	qbertSprite->SetTexture("QBert.png");
	qbertSprite->SetPosition(310, 60);
	qbertSprite->SetSourceRect(127, 0, 32, 32);

	qbert->AddComponent(qbertSprite);
	qbert->AddComponent(qbertGrid);
	qbert->AddComponent(qSubject);

	//Spawning the field
	for (int x = 0; x < pyramidHeight; ++x)
	{
		for (int y = 0; y < pyramidHeight - x; ++y)
		{
			go = std::make_shared<GameObject>();
			RenderComponent* tileSprite = new RenderComponent{ go.get() };
			GridComponent* tileGrid = new GridComponent{ go.get() };
			QBertObserver* tileObserver = new QBertObserver{ go.get() };
			qSubject->AddObserver(tileObserver);
			tileSprite->SetTexture("CubeBase.png");
			tileSprite->SetPosition(100 + (32.f * y) + (64.f * x), 360 - (48.f * y));
			tileGrid->SetGrid(x, y);
			gm.GetInstance().AddTilesLeft(1);

			go->AddComponent(tileSprite);
			go->AddComponent(tileGrid);
			go->AddComponent(tileObserver);
			gameScene.Add(go);
		}
	}

	// Spawning coily
	auto coily = std::make_shared<GameObject>();
	RenderComponent* coilySprite = new RenderComponent{ coily.get() };
	GridComponent* coilyGrid = new GridComponent{ coily.get() };
	MoveComponent* coilyMovement = new MoveComponent{ coily.get() };
	CoilyObserver* coilyObserver = new CoilyObserver{ coily.get() };
	coilyGrid->SetGrid(0, 6);
	coilySprite->SetTexture("CoilyEgg.png");
	coilySprite->SetPosition(310, 60);
	coilyMovement->SetInterval(0.5f);
	coilyMovement->SetTarget(qbert.get());
	coily->AddComponent(coilySprite);
	coily->AddComponent(coilyGrid);
	coily->AddComponent(coilyMovement);
	coily->AddComponent(coilyObserver);
	gameScene.Add(coily);

	//Lives and score
	auto lives = std::make_shared<GameObject>();
	TextRenderComponent* livesSprite = new TextRenderComponent{ "Lives: 3", font2, lives.get() };
	ScoreComponent* livesScore = new ScoreComponent{ lives.get() };
	LivesObserver* livesObserver = new LivesObserver{ lives.get() };
	livesSprite->SetPosition(500, 10);
	livesScore->SetScoreType("Lives");
	livesScore->SetScore(gm.GetLives());
	
	lives->AddComponent(livesSprite);
	lives->AddComponent(livesScore);
	lives->AddComponent(livesObserver);
	gameScene.Add(lives);

	qSubject->AddObserver(gameObserver);
	qSubject->AddObserver(coilyObserver);
	qSubject->AddObserver(livesObserver);
	gameScene.Add(qbert);


	// Bind the controls
	auto& input = InputManager::GetInstance();
	input.BindCommand(ControllerButton::ButtonA, new MoveRightDownCommand(qbertSprite, qbertGrid, qSubject, qbert.get()));
	input.BindCommand(ControllerButton::ButtonX, new MoveLeftDownCommand(qbertSprite, qbertGrid, qSubject, qbert.get()));
	input.BindCommand(ControllerButton::ButtonB, new MoveRightUpCommand(qbertSprite, qbertGrid, qSubject, qbert.get()));
	input.BindCommand(ControllerButton::ButtonY, new MoveLeftUpCommand(qbertSprite, qbertGrid, qSubject, qbert.get()));

	input.BindCommand(SDL_SCANCODE_KP_3, new MoveRightDownCommand(qbertSprite, qbertGrid, qSubject, qbert.get()));
	input.BindCommand(SDL_SCANCODE_KP_1, new MoveLeftDownCommand(qbertSprite, qbertGrid, qSubject, qbert.get()));
	input.BindCommand(SDL_SCANCODE_KP_9, new MoveRightUpCommand(qbertSprite, qbertGrid, qSubject, qbert.get()));
	input.BindCommand(SDL_SCANCODE_KP_7, new MoveLeftUpCommand(qbertSprite, qbertGrid, qSubject, qbert.get()));
}

void Application::LoadGameMultiplayer() const
{
	auto& gameScene = SceneManager::GetInstance().CreateScene("GameSceneMulti");
	auto& gm = GameManager::GetInstance();

	gameScene.SetActive(false);

	gm.SetLives(3);

	// Background
	auto go = std::make_shared<GameObject>();
	auto back = std::make_shared<GameObject>();
	RenderComponent* backgroundSprite = new RenderComponent{ back.get() };
	GameObserver* gameObserver = new GameObserver{ back.get() };
	backgroundSprite->SetTexture("background.jpg");
	back->AddComponent(backgroundSprite);
	back->AddComponent(gameObserver);
	gameScene.Add(back);

	//FPS counter
	go = std::make_shared<GameObject>();
	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	TextRenderComponent* fpsSprite = new TextRenderComponent{ "FPS: ", font2, go.get() };
	TimeComponent* timeComp = new TimeComponent{ go.get() };
	fpsSprite->SetPosition(10, 10);
	go->AddComponent(fpsSprite);
	go->AddComponent(timeComp);
	gameScene.Add(go);

	// Spawning Qberts
	int pyramidHeight = 7;

	auto qbert1 = std::make_shared<GameObject>();
	auto qbert2 = std::make_shared<GameObject>();
	RenderComponent* qbertSprite1 = new RenderComponent{ qbert1.get() };
	RenderComponent* qbertSprite2 = new RenderComponent{ qbert2.get() };
	GridComponent* qbertGrid1 = new GridComponent{ qbert1.get() };
	GridComponent* qbertGrid2 = new GridComponent{ qbert2.get() };
	SubjectComponent* qSubject1 = new SubjectComponent{ qbert1.get() };
	SubjectComponent* qSubject2 = new SubjectComponent{ qbert2.get() };

	qbertGrid1->SetGrid(0, 0);
	qbertSprite1->SetTexture("QBert.png");
	qbertSprite1->SetPosition(118, 348);
	qbertSprite1->SetSourceRect(127, 0, 32, 32);

	qbertGrid2->SetGrid(6, 0);
	qbertSprite2->SetTexture("QBert.png");
	qbertSprite2->SetPosition(502, 348);
	qbertSprite2->SetSourceRect(127, 0, 32, 32);

	qbert1->AddComponent(qbertSprite1);
	qbert1->AddComponent(qbertGrid1);
	qbert1->AddComponent(qSubject1);

	qbert2->AddComponent(qbertSprite2);
	qbert2->AddComponent(qbertGrid2);
	qbert2->AddComponent(qSubject2);

	//Spawning the field
	for (int x = 0; x < pyramidHeight; ++x)
	{
		for (int y = 0; y < pyramidHeight - x; ++y)
		{
			go = std::make_shared<GameObject>();
			RenderComponent* tileSprite = new RenderComponent{ go.get() };
			GridComponent* tileGrid = new GridComponent{ go.get() };
			QBertObserver* tileObserver = new QBertObserver{ go.get() };
			qSubject1->AddObserver(tileObserver);
			qSubject2->AddObserver(tileObserver);
			tileSprite->SetTexture("CubeBase.png");
			tileSprite->SetPosition(100 + (32.f * y) + (64.f * x), 360 - (48.f * y));
			tileGrid->SetGrid(x, y);
			gm.GetInstance().AddTilesLeft(1);

			go->AddComponent(tileSprite);
			go->AddComponent(tileGrid);
			go->AddComponent(tileObserver);
			gameScene.Add(go);
		}
	}

	// Spawning coily
	auto coily = std::make_shared<GameObject>();
	RenderComponent* coilySprite = new RenderComponent{ coily.get() };
	GridComponent* coilyGrid = new GridComponent{ coily.get() };
	MoveComponent* coilyMovement = new MoveComponent{ coily.get() };
	CoilyObserver* coilyObserver = new CoilyObserver{ coily.get() };
	coilyGrid->SetGrid(0, 6);
	coilySprite->SetTexture("CoilyEgg.png");
	coilySprite->SetPosition(310, 60);
	coilyMovement->SetInterval(0.5f);
	coilyMovement->SetTarget(qbert1.get());
	coily->AddComponent(coilySprite);
	coily->AddComponent(coilyGrid);
	coily->AddComponent(coilyMovement);
	coily->AddComponent(coilyObserver);
	gameScene.Add(coily);

	//Lives and score
	auto lives = std::make_shared<GameObject>();
	TextRenderComponent* livesSprite = new TextRenderComponent{ "Lives: 3", font2, lives.get() };
	ScoreComponent* livesScore = new ScoreComponent{ lives.get() };
	LivesObserver* livesObserver = new LivesObserver{ lives.get() };
	livesSprite->SetPosition(500, 10);
	livesScore->SetScoreType("Lives");
	livesScore->SetScore(gm.GetLives());

	lives->AddComponent(livesSprite);
	lives->AddComponent(livesScore);
	lives->AddComponent(livesObserver);
	gameScene.Add(lives);

	qSubject1->AddObserver(gameObserver);
	qSubject1->AddObserver(coilyObserver);
	qSubject2->AddObserver(gameObserver);
	qSubject1->AddObserver(livesObserver);
	qSubject2->AddObserver(livesObserver);
	
	gameScene.Add(qbert1);
	gameScene.Add(qbert2);


	// Bind the controls
	auto& input = InputManager::GetInstance();
	input.BindCommand(ControllerButton::ButtonA, new MoveRightDownCommand(qbertSprite1, qbertGrid1, qSubject1, qbert1.get()));
	input.BindCommand(ControllerButton::ButtonX, new MoveLeftDownCommand(qbertSprite1, qbertGrid1, qSubject1, qbert1.get()));
	input.BindCommand(ControllerButton::ButtonB, new MoveRightUpCommand(qbertSprite1, qbertGrid1, qSubject1, qbert1.get()));
	input.BindCommand(ControllerButton::ButtonY, new MoveLeftUpCommand(qbertSprite1, qbertGrid1, qSubject1, qbert1.get()));
	
	input.BindCommand(SDL_SCANCODE_KP_3, new MoveRightDownCommand(qbertSprite2, qbertGrid2, qSubject2, qbert2.get()));
	input.BindCommand(SDL_SCANCODE_KP_1, new MoveLeftDownCommand(qbertSprite2, qbertGrid2, qSubject2, qbert2.get()));
	input.BindCommand(SDL_SCANCODE_KP_9, new MoveRightUpCommand(qbertSprite2, qbertGrid2, qSubject2, qbert2.get()));
	input.BindCommand(SDL_SCANCODE_KP_7, new MoveLeftUpCommand(qbertSprite2, qbertGrid2, qSubject2, qbert2.get()));
}

void Application::LoadMainMenu() const
{
	auto& mainMenu = SceneManager::GetInstance().CreateScene("MainMenu");

	auto back = std::make_shared<GameObject>();
	RenderComponent* backgroundSprite = new RenderComponent{ back.get() };
	backgroundSprite->SetTexture("background.jpg");
	back->AddComponent(backgroundSprite);
	mainMenu.Add(back);
}
