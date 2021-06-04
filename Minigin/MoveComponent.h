#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

class MoveComponent : public BaseComponent
{
public:
	explicit MoveComponent(GameObject* parent);
	~MoveComponent();

	void Update(float deltaTime) override;
	void Render() const override;
	void SetInterval(float time);
	void SetTarget(GameObject* go);
	void SetMoveMethod(MoveMethod method);

private:
	void Move();
	void CheckHit(int2 grid, int2 otherGrid);
	
	float m_AccuTime;
	float m_Interval;

	GameObject* m_Target;

	MoveMethod m_Method = MoveMethod::RandomDown;
};

