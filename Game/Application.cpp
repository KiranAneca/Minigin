#include "Application.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include <memory>
#include <SDL.h>

#include "Observer.h"
#include "SubjectComponent.h"


void Application::InitializeApplication()
{
}

void Application::LoadApllication() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	RenderComponent* prc1 = new RenderComponent{ go.get() };
	prc1->SetTexture("background.jpg");
	go->AddComponent(prc1);
	scene.Add(go);

	// Spawning Qbert
	int pyramidHeight = 7;
	
	auto qbert = std::make_shared<GameObject>();
	qbert = std::make_shared<GameObject>();
	RenderComponent* prc4 = new RenderComponent{ qbert.get() };
	GridComponent* pgc2 = new GridComponent{ qbert.get() };
	SubjectComponent* qSubject = new SubjectComponent{ qbert.get() };

	pgc2->SetGrid(0, pyramidHeight - 1);
	prc4->SetTexture("QBert.png");
	prc4->SetPosition(310, 60);
	prc4->SetSourceRect(127, 0, 32, 32);

	qbert->AddComponent(prc4);
	qbert->AddComponent(pgc2);
	qbert->AddComponent(qSubject);

	//Spawning the field
	for (int x = 0; x < pyramidHeight; ++x)
	{
		for (int y = 0; y < pyramidHeight - x; ++y)
		{
			go = std::make_shared<GameObject>();
			RenderComponent* prc3 = new RenderComponent{ go.get() };
			GridComponent* pgc1 = new GridComponent{ go.get() };
			Observer* poc1 = new Observer{ go.get() };
			qSubject->AddObserver(poc1);
			prc3->SetTexture("CubeBase.png");
			prc3->SetPosition(100 + (32.f * y) + (64.f * x), 360 - (48.f * y));
			pgc1->SetGrid(x, y);
			
			go->AddComponent(prc3);
			go->AddComponent(pgc1);
			go->AddComponent(poc1);
			scene.Add(go);
		}
	}

	scene.Add(qbert);

	go = std::make_shared<GameObject>();
	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	TextRenderComponent* ptc2 = new TextRenderComponent{ "FPS: ", font2, go.get() };
	TimeComponent* pttx1 = new TimeComponent{ go.get() };
	ptc2->SetPosition(10, 10);
	go->AddComponent(ptc2);
	go->AddComponent(pttx1);
	scene.Add(go);

	
	// Bind the controls
	auto& input = InputManager::GetInstance();
	input.BindCommand(ControllerButton::ButtonA, new MoveRightDownCommand(prc4, pgc2, qSubject, qbert.get()));
	input.BindCommand(ControllerButton::ButtonX, new MoveLeftDownCommand(prc4, pgc2, qSubject, qbert.get()));
	input.BindCommand(ControllerButton::ButtonB, new MoveRightUpCommand(prc4, pgc2, qSubject, qbert.get()));
	input.BindCommand(ControllerButton::ButtonY, new MoveLeftUpCommand(prc4, pgc2, qSubject, qbert.get()));

	input.BindCommand(SDL_SCANCODE_KP_3, new MoveRightDownCommand(prc4, pgc2, qSubject, qbert.get()));
	input.BindCommand(SDL_SCANCODE_KP_1, new MoveLeftDownCommand(prc4, pgc2, qSubject, qbert.get()));
	input.BindCommand(SDL_SCANCODE_KP_9, new MoveRightUpCommand(prc4, pgc2, qSubject, qbert.get()));
	input.BindCommand(SDL_SCANCODE_KP_7, new MoveLeftUpCommand(prc4, pgc2, qSubject, qbert.get()));
}

void Application::CleanupApplication()
{
}

void Application::RunApplication()
{
}
