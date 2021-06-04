#pragma once
#include "Observer.h"
class CoilyObserver : public Observer
{
public:
	explicit CoilyObserver(GameObject* parent);
	void Notify(const GameObject& actor, Event event) override;

	void Update(float deltaTime) override;
	void Render() const override;
};

