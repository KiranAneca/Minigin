#include "ScoreObserver.h"
#include "GameManager.h"
#include "ScoreComponent.h"

ScoreObserver::ScoreObserver(GameObject* parent)
	: Observer(parent)
{
}

void ScoreObserver::Notify(const GameObject&, Event event)
{
	auto& gm = GameManager::GetInstance();

	auto score = m_Parent->GetComponent<ScoreComponent>();

	switch (event)
	{
	case Event::MoveTile:
		break;
	case Event::Died:
		break;
	case Event::LevelCleared:
		gm.AddScore(50);
		score->SetScore(gm.GetScore());
		break;
	case Event::CompleteTile:
		gm.AddScore(25);
		score->SetScore(gm.GetScore());
		break;
	}
}

void ScoreObserver::Update(float)
{
}

void ScoreObserver::Render() const
{
}
