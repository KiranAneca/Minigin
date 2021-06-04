#include "Application.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Scene.h"
#include <memory>
#include <SDL.h>

#include "QBertObserver.h"
#include "SubjectComponent.h"
#include "GameObserver.h"
#include "ScoreComponent.h"


void Application::InitializeApplication()
{
}

void Application::LoadApllication() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto& gm = GameManager::GetInstance();

	gm.SetLives(3);

	// Background
	auto go = std::make_shared<GameObject>();
	RenderComponent* backgroundSprite = new RenderComponent{ go.get() };
	GameObserver* gameObserver = new GameObserver{ go.get() };
	backgroundSprite->SetTexture("background.jpg");
	go->AddComponent(backgroundSprite);
	go->AddComponent(gameObserver);
	scene.Add(go);

	//FPS counter
	go = std::make_shared<GameObject>();
	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	TextRenderComponent* fpsSprite = new TextRenderComponent{ "FPS: ", font2, go.get() };
	TimeComponent* timeComp = new TimeComponent{ go.get() };
	fpsSprite->SetPosition(10, 10);
	go->AddComponent(fpsSprite);
	go->AddComponent(timeComp);
	scene.Add(go);

	// Spawning Qbert
	int pyramidHeight = 7;
	
	auto qbert = std::make_shared<GameObject>();
	qbert = std::make_shared<GameObject>();
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
			scene.Add(go);
		}
	}

	//Lives and score
	TextRenderComponent* livesSprite = new TextRenderComponent{ "Lives: 3", font2, qbert.get() };
	ScoreComponent* livesScore = new ScoreComponent{ qbert.get() };
	livesSprite->SetPosition(500, 10);
	livesScore->SetScoreType("Lives");
	livesScore->SetScore(gm.GetLives());
	qbert->AddComponent(livesSprite);
	qbert->AddComponent(livesScore);

	qSubject->AddObserver(gameObserver);
	scene.Add(qbert);

	
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

void Application::CleanupApplication()
{
}

void Application::RunApplication()
{
}
