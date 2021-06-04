#include "CoilyObserver.h"
#include <Windows.h>
#include "GridComponent.h"
#include "RenderComponent.h"
#include "MoveComponent.h"

CoilyObserver::CoilyObserver(GameObject* parent)
	:Observer(parent)
{
}

void CoilyObserver::Notify(const GameObject& actor, Event event)
{
	switch (event)
	{
	case Event::MoveTile:
		break;
	case Event::Died:
		m_Parent->GetComponent<GridComponent>()->SetGrid(0, 6);
		m_Parent->GetComponent<RenderComponent>()->SetTexture("CoilyEgg.png");
		m_Parent->GetComponent<RenderComponent>()->SetPosition(310, 60);
		m_Parent->GetComponent<MoveComponent>()->SetMoveMethod(MoveMethod::RandomDown);
		break;
	case Event::LevelCleared:
		m_Parent->GetComponent<GridComponent>()->SetGrid(0, 6);
		m_Parent->GetComponent<RenderComponent>()->SetTexture("CoilyEgg.png");
		m_Parent->GetComponent<RenderComponent>()->SetPosition(310, 60);
		m_Parent->GetComponent<MoveComponent>()->SetMoveMethod(MoveMethod::RandomDown);
		break;
	}

	UNREFERENCED_PARAMETER(actor);
}

void CoilyObserver::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void CoilyObserver::Render() const
{
}
