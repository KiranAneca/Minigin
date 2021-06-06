#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

class MoveComponent : public BaseComponent
{
public:
	explicit MoveComponent(GameObject* parent);
	virtual ~MoveComponent();

	virtual void Update(float deltaTime) override;
	virtual void Render() const override;
	MoveEvent GetEvent() const;
	void SetInterval(float time);
	void SetTarget(GameObject* go);
	void SetMoveMethod(MoveMethod method);
	void SetMoveEvent(MoveEvent event);
	bool CanMove() const;
	virtual void Move();
protected:
	void CheckHit(int2 grid, int2 otherGrid, MoveEvent otherEvent);
	
	float m_AccuTime;
	float m_Interval;
	bool m_CanMove;

	GameObject* m_Target;

	MoveMethod m_Method = MoveMethod::RandomDown;
	MoveEvent m_Event = MoveEvent::Nothing;
};

