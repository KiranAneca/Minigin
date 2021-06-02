#pragma once

// Components
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextRenderComponent.h"
#include "TimeComponent.h"

struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void StartGame(int playerAmount);
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};

		GameObject m_FPSTimer;
		int m_AmountOfPlayers;
		
		std::vector<GameObject*> m_pPlayers;
	};
}