#pragma once
#include "GameObject.h"
#include "Helpers.h"

	class Observer : public BaseComponent
	{
	public:
		Observer(GameObject* parent);
		virtual void Notify(const GameObject& actor, Event event);

		void Update(float deltaTime) override;
		void Render() const override;
	};

