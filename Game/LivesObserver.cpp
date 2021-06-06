#include "LivesObserver.h"
#include "GameManager.h"
#include "ScoreComponent.h"
#include "TextRenderComponent.h"
#include "GridComponent.h"
#include <iostream>

LivesObserver::LivesObserver(GameObject* parent)
	:Observer(parent)
{
}

void LivesObserver::Notify(const GameObject&, Event event)
{
	auto& gm = GameManager::GetInstance();

	auto score = m_Parent->GetComponent<ScoreComponent>();

	switch (event)
	{
	case Event::MoveTile:
		break;
	case Event::Died:
		score->SetScore(gm.GetLives());
		//m_Parent->GetComponent<TextRenderComponent>()->SetText(score->GetScoreType() + ": " + std::to_string(score->GetScore()));
		break;
	case Event::LevelCleared:
		score->SetScore(3);
		std::cout << "Level complete\n";
		break;
	}
}

void LivesObserver::Update(float)
{
}

void LivesObserver::Render() const
{
}
