#pragma once
#include "Observer.h"
class QBertObserver : public Observer
{
public:
	explicit QBertObserver(GameObject* parent);
	void Notify(const GameObject& actor, Event event) override;

	void Update(float deltaTime) override;
	void Render() const override;
};

