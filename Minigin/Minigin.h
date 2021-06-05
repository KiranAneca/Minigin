#pragma once

// Components
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextRenderComponent.h"
#include "TimeComponent.h"


struct SDL_Window;
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void StartGame(int playerAmount);
		void Cleanup();
		void Run();

		virtual void InitializeApplication() = 0;
		virtual void LoadApllication() const = 0;
		virtual void CleanupApplication() = 0;
		virtual void RunApplication() = 0;

		SDL_Window* GetWindow() const;
	
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};

		GameObject m_FPSTimer;
		int m_AmountOfPlayers;
		
		std::vector<GameObject*> m_pPlayers;
	};