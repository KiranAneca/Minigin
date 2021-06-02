#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

#include "GridComponent.h"

// GUI
#include <imgui.h>
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	RenderComponent* prc1 = new RenderComponent{ go.get() };
	prc1->SetTexture("background.jpg");
	go->AddComponent(prc1);
	scene.Add(go);

	//Spawning the field
	int pyramidHeight = 7;
	for(int y = 0; y < pyramidHeight; ++y)
	{
		for(int x = 0; x < pyramidHeight - y; ++x)
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
	go = std::make_shared<GameObject>();
	RenderComponent* prc4 = new RenderComponent{ go.get() };
	GridComponent* pgc2 = new GridComponent{ go.get() };
	pgc2->SetGrid(pyramidHeight, pyramidHeight);
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
}

void dae::Minigin::StartGame(int playerAmount)
{
	auto& scene = SceneManager::GetInstance().GetActiveScene();
	
	for(int i = 0; i < playerAmount; ++i)
	{
		auto go = std::make_shared<GameObject>();
		m_pPlayers.push_back(go.get());
		scene.Add(go);
	}
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			renderer.Render();
			renderer.RenderUI(this);

			lastTime = currentTime;
			
			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
