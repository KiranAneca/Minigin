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
	m_AccuTime += deltaTime;
	if(m_AccuTime >= m_Interval)
	{
		m_AccuTime = 0.f;
		Move();
	}
}

void MoveComponent::Render() const
{
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
	CheckHit(grid->GetGrid(), targetGrid->GetGrid()); // Collision detection
}

void MoveComponent::CheckHit(int2 grid, int2 otherGrid)
{
	if(grid.x == otherGrid.x && grid.y == otherGrid.y)
	{
		m_Target->GetComponent<SubjectComponent>()->Notify(*m_Target, Event::Died);
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
