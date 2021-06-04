#pragma once
#include "Observer.h"

class GameObserver : public Observer
{
public:
	explicit GameObserver(GameObject* parent);
	void Notify(const GameObject& actor, Event event) override;

	void Update(float deltaTime) override;
	void Render() const override;
};

