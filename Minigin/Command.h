#pragma once
#include "RenderComponent.h"
#include "GridComponent.h"
#include "Observer.h"
#include "SubjectComponent.h"

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
	MoveLeftDownCommand(RenderComponent* ren, GridComponent* grid, SubjectComponent* sub, GameObject* go)
		: Command()
	, m_Ren(ren)
	, m_Grid(grid)
	, m_Sub(sub)
	, m_Go(go) {}
	void Execute() override
	{
		float2 pos = m_Ren->GetPosition();
		int2 grid = m_Grid->GetGrid();
		if(grid.y > 0)
		{
			m_Ren->SetPosition(pos.x - 32, pos.y + 48);
			m_Grid->SetGrid(grid.x, grid.y - 1);
			//std::cout << grid.x << " " << grid.y - 1 << std::endl;
			m_Sub->Notify(*m_Go, Event::MoveTile);
		}
		else
		{
			m_Grid->SetGrid(0, 6);
			m_Sub->Notify(*m_Go, Event::Died);
			m_Ren->SetPosition(310, 60);
		}
	};

private:
	RenderComponent* m_Ren;
	GridComponent* m_Grid;
	SubjectComponent* m_Sub;
	GameObject* m_Go;
};

class MoveRightDownCommand : public Command
{
public:
	MoveRightDownCommand(RenderComponent* ren, GridComponent* grid, SubjectComponent* sub, GameObject* go)
		: Command()
		, m_Ren(ren)
		, m_Grid(grid)
		, m_Sub(sub)
		, m_Go(go) {}
	void Execute() override
	{
		float2 pos = m_Ren->GetPosition();
		int2 grid = m_Grid->GetGrid();
		if (grid.y > 0)
		{
			m_Ren->SetPosition(pos.x + 32, pos.y + 48);
			m_Grid->SetGrid(grid.x + 1, grid.y - 1);
			//std::cout << grid.x + 1 << " " << grid.y - 1 << std::endl;
			m_Sub->Notify(*m_Go, Event::MoveTile);
		}
		else
		{
			m_Grid->SetGrid(0, 6);
			m_Sub->Notify(*m_Go, Event::Died);
			m_Ren->SetPosition(310, 60);
		}
	};

private:
	RenderComponent* m_Ren;
	GridComponent* m_Grid;
	SubjectComponent* m_Sub;
	GameObject* m_Go;
};

class MoveRightUpCommand : public Command
{
public:
	MoveRightUpCommand(RenderComponent* ren, GridComponent* grid, SubjectComponent* sub, GameObject* go)
		: Command()
		, m_Ren(ren)
		, m_Grid(grid)
		, m_Sub(sub)
		, m_Go(go) {}
	void Execute() override
	{
		float2 pos = m_Ren->GetPosition();
		int2 grid = m_Grid->GetGrid();
		if (grid.x + grid.y < 6)
		{
			m_Ren->SetPosition(pos.x + 32, pos.y - 48);
			m_Grid->SetGrid(grid.x, grid.y + 1);
			//std::cout << grid.x + grid.y;
			m_Sub->Notify(*m_Go, Event::MoveTile);
		}
		else
		{
			m_Grid->SetGrid(0, 6);
			m_Sub->Notify(*m_Go, Event::Died);
			m_Ren->SetPosition(310, 60);
		}
	};

private:
	RenderComponent* m_Ren;
	GridComponent* m_Grid;
	SubjectComponent* m_Sub;
	GameObject* m_Go;
};

class MoveLeftUpCommand : public Command
{
public:
	MoveLeftUpCommand(RenderComponent* ren, GridComponent* grid, SubjectComponent* sub, GameObject* go)
		: Command()
		, m_Ren(ren)
		, m_Grid(grid)
		, m_Sub(sub)
		, m_Go(go) {}
	void Execute() override
	{
		float2 pos = m_Ren->GetPosition();
		int2 grid = m_Grid->GetGrid();
		if (grid.x > 0)
		{
			m_Ren->SetPosition(pos.x - 32, pos.y - 48);
			m_Grid->SetGrid(grid.x - 1, grid.y + 1);
			//std::cout << grid.x - 1 << " " << grid.y + 1 << std::endl;
			m_Sub->Notify(*m_Go, Event::MoveTile);
		}
		else
		{
			m_Grid->SetGrid(0, 6);
			m_Sub->Notify(*m_Go, Event::Died);
			m_Ren->SetPosition(310, 60);
		}
	};

private:
	RenderComponent* m_Ren;
	GridComponent* m_Grid;
	SubjectComponent* m_Sub;
	GameObject* m_Go;
};
