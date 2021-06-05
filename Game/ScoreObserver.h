#pragma once
#include "Observer.h"

class ScoreObserver : public Observer
{
public:
	explicit ScoreObserver(GameObject* parent);
	void Notify(const GameObject& actor, Event event) override;

	void Update(float deltaTime) override;
	void Render() const override;
};

