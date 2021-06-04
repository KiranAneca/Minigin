#pragma once
#include "Observer.h"

class LivesObserver : public Observer
{
public:
	explicit LivesObserver(GameObject* parent);
	void Notify(const GameObject& actor, Event event) override;

	void Update(float deltaTime) override;
	void Render() const override;
};

