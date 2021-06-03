#include "MiniginPCH.h"
#include "Observer.h"
#include "GridComponent.h"
#include "RenderComponent.h"

Observer::Observer(GameObject* parent)
	:BaseComponent(parent)
{
}

void Observer::Notify(const GameObject& actor, Event event)
{
	UNREFERENCED_PARAMETER(actor);
	int2 pos = m_Parent->GetComponent<GridComponent>()->GetGrid();
	int2 otherPos = actor.GetComponent<GridComponent>()->GetGrid();
	switch(event)
	{
	case Event::ColorTile:
		if(pos.x == otherPos.x && pos.y == otherPos.y)
		{
			m_Parent->GetComponent<RenderComponent>()->SetTexture("CubeJumped.png");
		}
		break;
	case Event::Died:
		break;
	}
}

void Observer::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void Observer::Render() const
{
}
