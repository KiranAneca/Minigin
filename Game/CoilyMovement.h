#pragma once
#include "MoveComponent.h"

class CoilyMovement : public MoveComponent
{
public:
	explicit CoilyMovement(GameObject* parent);
	~CoilyMovement();

	void Update(float deltaTime) override;
	void Render() const override;
	void Move() override;

	void SetGainControl(bool active);
	bool HasControl() const;

private:
	bool m_GainControl = false;
};

