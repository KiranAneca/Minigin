#include "GameObserver.h"
#include "GameManager.h"
#include "ScoreComponent.h"
#include "RenderComponent.h"
#include "GridComponent.h"
#include "SceneManager.h"
#include <iostream>
#include <windows.h>

GameObserver::GameObserver(GameObject* parent)
	: Observer(parent)
{
}

void GameObserver::Notify(const GameObject& actor, Event event)
{
	auto& gm = GameManager::GetInstance();
	UNREFERENCED_PARAMETER(actor);

	auto grid = actor.GetComponent<GridComponent>();

	switch (event)
	{
	case Event::MoveTile:
		break;
	case Event::Died:
		gm.LoseLife();
		std::cout << gm.GetLives() << " lifes left\n";
		grid->SetGrid(grid->GetStartGrid());
		actor.GetComponent<RenderComponent>()->SetPosition(118.f + (32.f * grid->GetStartGrid().y) + (64.f * grid->GetStartGrid().x), 348.f - (48.f * grid->GetStartGrid().y));
		if(gm.GetLives() == 0)
		{
			auto& sceneManager = SceneManager::GetInstance();
			sceneManager.SetSceneActive(true, "MainMenu");
			sceneManager.DeleteScene("GameSceneSingle");
			sceneManager.DeleteScene("GameSceneMulti");
			sceneManager.DeleteScene("GameSceneVersus");

			gm.SetSeeMenu(true);
		}
		break;
	case Event::LevelCleared:
		grid->SetGrid(grid->GetStartGrid());
		actor.GetComponent<RenderComponent>()->SetPosition(118.f + (32.f * grid->GetStartGrid().y) + (64.f * grid->GetStartGrid().x), 348.f - (48.f * grid->GetStartGrid().y));
		std::cout << "Level complete\n";
		gm.SetLevel(gm.GetLevel() + 1);
		if(gm.GetLevel() == 2)
		{
			gm.SetGameType(GameType::Double);
		}
		else if(gm.GetLevel() == 3)
		{
			gm.SetGameType(GameType::Return);
		}
		break;
	}
}

void GameObserver::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void GameObserver::Render() const
{
}
