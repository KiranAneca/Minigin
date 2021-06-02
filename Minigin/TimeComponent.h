#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TimeComponent : public BaseComponent
	{
	public:
	TimeComponent(GameObject* parent);
	~TimeComponent();
		
		void Update(float deltaTime) override;
		void Render() const override;
		int GetFrames() const;
	
	private:
		float m_SecondCounter;
		int m_Frames;
	};
}

