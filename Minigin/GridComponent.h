#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

namespace dae
{
	class Texture2D;
	class GridComponent : public BaseComponent
	{
	public:
		explicit GridComponent(GameObject* parent);
		~GridComponent();

		void Update(float deltaTime) override;

		void SetGrid(int2 grid);
		void SetGrid(int x, int y);
		int2 GetGrid() const;
		
		void Render() const override;
	private:
		int2 m_Grid;
	};
}

