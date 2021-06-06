#include "MiniginPCH.h"
#include "MoveComponent.h"
#include "GridComponent.h"
#include "RenderComponent.h"
#include "SubjectComponent.h"

#include "GameObject.h"

MoveComponent::MoveComponent(GameObject* parent)
	: BaseComponent(parent)
    , m_Target(parent)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltaTime)
{
	if(!m_CanMove)
	{
		m_AccuTime += deltaTime;
		if (m_AccuTime >= m_Interval)
		{
			m_AccuTime = 0.f;
			m_CanMove = true;
		}
	}
	if(m_CanMove && m_Method != MoveMethod::PlayerControlled)
	{
		Move();
		m_CanMove = false;
	}
}

void MoveComponent::Render() const
{
}

MoveEvent MoveComponent::GetEvent() const
{
	return m_Event;
}

void MoveComponent::Move() 
{
	auto grid = m_Parent->GetComponent<GridComponent>();
	auto ren = m_Parent->GetComponent<RenderComponent>();

	auto targetGrid = m_Target->GetComponent<GridComponent>();
	
	if(m_Method == MoveMethod::RandomDown)
	{
		if(std::rand() % 2 == 0) // Left
		{
			grid->SetGrid(grid->GetGrid().x, grid->GetGrid().y - 1);
			ren->SetPosition(ren->GetPosition().x - 32, ren->GetPosition().y + 48);
		}
		else // Right
		{
			grid->SetGrid(grid->GetGrid().x + 1, grid->GetGrid().y - 1);
			ren->SetPosition(ren->GetPosition().x + 32, ren->GetPosition().y + 48);
		}
		if (grid->GetGrid().y == 0) m_Method = MoveMethod::TowardsPlayer;
	}
	else if(m_Method == MoveMethod::PlayerControlled)
	{
		m_CanMove = false;
	}
	else if(m_Method == MoveMethod::TowardsPlayer)
	{
		if(targetGrid == nullptr) return;
			
		if(grid->GetGrid().y <= targetGrid->GetGrid().y) // Qbert is above you
		{
			if(grid->GetGrid().x > targetGrid->GetGrid().x) // QBert is to the left of you
			{
				grid->SetGrid(grid->GetGrid().x - 1, grid->GetGrid().y + 1);
				ren->SetPosition(ren->GetPosition().x - 32, ren->GetPosition().y - 48);
			}
			else // QBert is to the right of you
			{
				grid->SetGrid(grid->GetGrid().x, grid->GetGrid().y + 1);
				ren->SetPosition(ren->GetPosition().x + 32, ren->GetPosition().y - 48);
			}
		}
		else // QBert is under you or on the same line
		{
			if (grid->GetGrid().x >= targetGrid->GetGrid().x) // QBert is to the left of you
			{
				grid->SetGrid(grid->GetGrid().x, grid->GetGrid().y - 1);
				ren->SetPosition(ren->GetPosition().x - 32, ren->GetPosition().y + 48);
			}
			else // QBert is to the right of you
			{
				grid->SetGrid(grid->GetGrid().x + 1, grid->GetGrid().y - 1);
				ren->SetPosition(ren->GetPosition().x + 32, ren->GetPosition().y + 48);
			}
		}
	}
	CheckHit(grid->GetGrid(), targetGrid->GetGrid(), m_Target->GetComponent<MoveComponent>()->GetEvent()); // Collision detection
}

void MoveComponent::CheckHit(int2 grid, int2 otherGrid, MoveEvent otherEvent)
{
	if(m_Event == MoveEvent::KillPlayer || otherEvent == MoveEvent::KillPlayer)
	{
		if (grid.x == otherGrid.x && grid.y == otherGrid.y)
		{
			auto target = m_Target->GetComponent<SubjectComponent>();
			auto parent = m_Parent->GetComponent<SubjectComponent>();
			if (target != nullptr) target->Notify(*m_Target, Event::Died);
			if (parent != nullptr) parent->Notify(*m_Parent, Event::Died);
			//m_Target->GetComponent<SubjectComponent>()->Notify(*m_Target, Event::Died);
		}
	}
}

void MoveComponent::SetInterval(float time)
{
	m_Interval = time;
}

void MoveComponent::SetTarget(GameObject* go)
{
	m_Target = go;
}

void MoveComponent::SetMoveMethod(MoveMethod method)
{
	m_Method = method;
}

void MoveComponent::SetMoveEvent(MoveEvent event)
{
	m_Event = event;
}

bool MoveComponent::CanMove() const
{
	return m_CanMove;
}
