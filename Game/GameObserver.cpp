#include "GameObserver.h"
#include "GameManager.h"
#include "ScoreComponent.h"
#include "RenderComponent.h"
#include "GridComponent.h"
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

	switch (event)
	{
	case Event::MoveTile:
		break;
	case Event::Died:
		gm.LoseLife();
		std::cout << gm.GetLives() << " lifes left\n";
		actor.GetComponent<RenderComponent>()->SetPosition(310, 60);
		actor.GetComponent<GridComponent>()->SetGrid(0, 6);
		break;
	case Event::LevelCleared:
		actor.GetComponent<RenderComponent>()->SetPosition(310, 60);
		actor.GetComponent<GridComponent>()->SetGrid(0, 6);
		std::cout << "Level complete\n";
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
