#include "CoilyObserver.h"
#include "GridComponent.h"
#include "RenderComponent.h"
#include "MoveComponent.h"

CoilyObserver::CoilyObserver(GameObject* parent)
	:Observer(parent)
{
}

void CoilyObserver::Notify(const GameObject&, Event event)
{
	auto ren = m_Parent->GetComponent<RenderComponent>();
	auto mov = m_Parent->GetComponent<MoveComponent>();
	switch (event)
	{
	case Event::MoveTile:
		break;
	case Event::Died:
		m_Parent->GetComponent<GridComponent>()->SetGrid(0, 6);
		ren->SetTexture("CoilyEgg.png");
		ren->SetPosition(310, 60);
		mov->SetMoveMethod(MoveMethod::RandomDown);
		mov->SetMoveEvent(MoveEvent::Nothing);
		break;
	case Event::LevelCleared:
		m_Parent->GetComponent<GridComponent>()->SetGrid(0, 6);
		ren->SetTexture("CoilyEgg.png");
		ren->SetPosition(310, 60);
		mov->SetMoveMethod(MoveMethod::RandomDown);
		mov->SetMoveEvent(MoveEvent::Nothing);
		break;
	}

}

void CoilyObserver::Update(float)
{
}

void CoilyObserver::Render() const
{
}
