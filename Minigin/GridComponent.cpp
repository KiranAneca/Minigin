#include "MiniginPCH.h"
#include "GridComponent.h"

GridComponent::GridComponent(GameObject* parent)
	:BaseComponent(parent)
{
	
}

GridComponent::~GridComponent()
{
}

void GridComponent::Update(float)
{
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

void GridComponent::SetStartGrid(int2 grid)
{
	m_StartGrid = grid;
}

void GridComponent::SetStartGrid(int x, int y)
{
	m_StartGrid.x = x;
	m_StartGrid.y = y;
}

int2 GridComponent::GetGrid() const
{
	return m_Grid;
}

int2 GridComponent::GetStartGrid() const
{
	return m_StartGrid;
}

void GridComponent::Render() const
{
}

