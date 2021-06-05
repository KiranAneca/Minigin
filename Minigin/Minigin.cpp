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

void Minigin::Initialize()
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

	//Renderer::GetInstance().Init(m_Window);
	InitializeApplication();
}

/**
 * Code constructing the scene world starts here
 */
void Minigin::LoadGame() const
{
	LoadApllication();
}

void Minigin::StartGame(int playerAmount)
{
	auto& scene = SceneManager::GetInstance().GetActiveScene();
	
	for(int i = 0; i < playerAmount; ++i)
	{
		auto go = std::make_shared<GameObject>();
		m_pPlayers.push_back(go.get());
		scene.Add(go);
	}
}

void Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();

	CleanupApplication();
}

void Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("Data/");

	LoadGame();

	{
		//auto& renderer = Renderer::GetInstance();
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
			RunApplication();
			//renderer.Render();
			//renderer.RenderUI(this);

			lastTime = currentTime;

			
			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

struct SDL_Window* Minigin::GetWindow() const
{
	return m_Window;
}
