#include "CoilyMovement.h"

#include "GameObject.h"
#include "GridComponent.h"
#include "RenderComponent.h"

CoilyMovement::CoilyMovement(GameObject* parent)
	: MoveComponent(parent)
{
}

CoilyMovement::~CoilyMovement()
{
}

void CoilyMovement::Update(float deltaTime)
{
	MoveComponent::Update(deltaTime);
}

void CoilyMovement::Render() const
{
}

void CoilyMovement::Move()
{
	MoveComponent::Move();
	auto ren = m_Parent->GetComponent<RenderComponent>();
	if(m_Event == MoveEvent::Nothing)
	{
		if (m_Parent->GetComponent<GridComponent>()->GetGrid().y == 0)
		{
			ren->SetTexture("Coily.png");
			ren->SetPosition(ren->GetPosition().x, ren->GetPosition().y - 30);
			m_Event = MoveEvent::KillPlayer;
		}
	}
}
