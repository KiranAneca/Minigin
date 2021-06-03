#pragma once
#include "RenderComponent.h"
#include "GridComponent.h"

#include "iostream"

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
	
};

class MoveLeftDownCommand : public Command
{
public:
	MoveLeftDownCommand(RenderComponent* ren, GridComponent* grid)
		: Command()
	, m_Ren(ren)
	, m_Grid(grid) {}
	void Execute() override
	{
		float2 pos = m_Ren->GetPosition();
		int2 grid = m_Grid->GetGrid();
		if(grid.y > 0)
		{
			m_Ren->SetPosition(pos.x - 32, pos.y + 48);
			m_Grid->SetGrid(grid.x - 1, grid.y - 1);
			//std::cout << grid.x - 1 << " " << grid.y - 1 << std::endl;
		}
	};

private:
	RenderComponent* m_Ren;
	GridComponent* m_Grid;
};

class MoveRightDownCommand : public Command
{
public:
	MoveRightDownCommand(RenderComponent* ren, GridComponent* grid)
		: Command()
		, m_Ren(ren)
		, m_Grid(grid) {}
	void Execute() override
	{
		float2 pos = m_Ren->GetPosition();
		int2 grid = m_Grid->GetGrid();
		if (grid.y > 0)
		{
			m_Ren->SetPosition(pos.x + 32, pos.y + 48);
			m_Grid->SetGrid(grid.x + 1, grid.y - 1);
			//std::cout << grid.x + 1 << " " << grid.y - 1 << std::endl;
		}
	};

private:
	RenderComponent* m_Ren;
	GridComponent* m_Grid;
};

class MoveRightUpCommand : public Command
{
public:
	MoveRightUpCommand(RenderComponent* ren, GridComponent* grid)
		: Command()
		, m_Ren(ren)
		, m_Grid(grid) {}
	void Execute() override
	{
		float2 pos = m_Ren->GetPosition();
		int2 grid = m_Grid->GetGrid();
		if (grid.x + grid.y < 12)
		{
			m_Ren->SetPosition(pos.x + 32, pos.y - 48);
			m_Grid->SetGrid(grid.x + 1, grid.y + 1);
			//std::cout << grid.x + 1 << " " << grid.y + 1 << std::endl;
		}
	};

private:
	RenderComponent* m_Ren;
	GridComponent* m_Grid;
};

class MoveLeftUpCommand : public Command
{
public:
	MoveLeftUpCommand(RenderComponent* ren, GridComponent* grid)
		: Command()
		, m_Ren(ren)
		, m_Grid(grid) {}
	void Execute() override
	{
		float2 pos = m_Ren->GetPosition();
		int2 grid = m_Grid->GetGrid();
		if (grid.x != grid.y)
		{
			m_Ren->SetPosition(pos.x - 32, pos.y - 48);
			m_Grid->SetGrid(grid.x - 1, grid.y + 1);
			//std::cout << grid.x - 1 << " " << grid.y + 1 << std::endl;
		}
	};

private:
	RenderComponent* m_Ren;
	GridComponent* m_Grid;
};
