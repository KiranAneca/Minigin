#include "MiniginPCH.h"
#include "GridComponent.h"

GridComponent::GridComponent(GameObject* parent)
	:BaseComponent(parent)
{
	
}

GridComponent::~GridComponent()
{
}

void GridComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void GridComponent::SetGrid(int2 grid)
{
	m_Grid = grid;
}

void GridComponent::SetGrid(int x, int y)
{
	m_Grid.x = x;
	m_Grid.y = y;
}

int2 GridComponent::GetGrid() const
{
	return m_Grid;
}

void GridComponent::Render() const
{
}

