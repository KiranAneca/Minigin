#include "Application.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include <memory>


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

	//Spawning the field
	int pyramidHeight = 7;
	for (int x = 0; x < pyramidHeight; ++x)
	{
		for (int y = 0; y < pyramidHeight - x; ++y)
		{
			go = std::make_shared<GameObject>();
			RenderComponent* prc3 = new RenderComponent{ go.get() };
			GridComponent* pgc1 = new GridComponent{ go.get() };
			prc3->SetTexture("CubeBase.png");
			prc3->SetPosition(100 + (32.f * y) + (64.f * x), 360 - (48.f * y));
			pgc1->SetGrid(x, y);

			go->AddComponent(prc3);
			go->AddComponent(pgc1);
			scene.Add(go);
		}
	}

	// Spawning Qbert
	auto qbert = std::make_shared<GameObject>();
	qbert = std::make_shared<GameObject>();
	RenderComponent* prc4 = new RenderComponent{ qbert.get() };
	GridComponent* pgc2 = new GridComponent{ qbert.get() };
	pgc2->SetGrid(pyramidHeight - 1, pyramidHeight - 1);
	prc4->SetTexture("QBert.png");
	prc4->SetPosition(310, 60);
	prc4->SetSourceRect(127, 0, 32, 32);

	go->AddComponent(prc4);
	go->AddComponent(pgc2);
	scene.Add(go);

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
	input.BindCommand(ControllerButton::ButtonA, new MoveRightDownCommand(prc4, pgc2));
	input.BindCommand(ControllerButton::ButtonX, new MoveLeftDownCommand(prc4, pgc2));
	input.BindCommand(ControllerButton::ButtonB, new MoveRightUpCommand(prc4, pgc2));
	input.BindCommand(ControllerButton::ButtonY, new MoveLeftUpCommand(prc4, pgc2));
}

void Application::CleanupApplication()
{
}

void Application::RunApplication()
{
}
