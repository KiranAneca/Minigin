#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

	class Texture2D;
	class GridComponent : public BaseComponent
	{
	public:
		explicit GridComponent(GameObject* parent);
		~GridComponent();

		void Update(float deltaTime) override;

		void SetGrid(int2 grid);
		void SetGrid(int x, int y);
		void SetStartGrid(int2 grid);
		void SetStartGrid(int x, int y);
		int2 GetGrid() const;
		int2 GetStartGrid() const;
		
		void Render() const override;
	private:
		int2 m_Grid;
		int2 m_StartGrid;
	};

