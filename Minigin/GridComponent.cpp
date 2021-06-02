#include "MiniginPCH.h"
#include "GridComponent.h"

dae::GridComponent::GridComponent(GameObject* parent)
	:BaseComponent(parent)
{
	
}

dae::GridComponent::~GridComponent()
{
}

void dae::GridComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void dae::GridComponent::SetGrid(int2 grid)
{
	m_Grid = grid;
}

void dae::GridComponent::SetGrid(int x, int y)
{
	m_Grid.x = x;
	m_Grid.y = y;
}

int2 dae::GridComponent::GetGrid() const
{
	return m_Grid;
}

void dae::GridComponent::Render() const
{
}

