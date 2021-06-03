#pragma once
#include "GameObject.h"
#include "Events.h"

	class Observer : public BaseComponent
	{
	public:
		Observer(GameObject* parent);
		void Notify(const GameObject& actor, Event event);

		void Update(float deltaTime) override;
		void Render() const override;
	};

