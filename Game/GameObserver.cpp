#include "GameObserver.h"
#include "GameManager.h"
#include "ScoreComponent.h"
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
		if (gm.GetTilesLeft() == 0)
		{
			std::cout << "Level complete\n";
		}
		break;
	case Event::Died:
		gm.LoseLife();
		std::cout << gm.GetLives() << " lifes left\n";
		actor.GetComponent<ScoreComponent>()->SetScore(gm.GetLives());
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
