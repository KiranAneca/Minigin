#pragma once
#include "GameObject.h"
#include "Events.h"

	class Observer
	{
	public:
		Observer();
		void Notify(const GameObject& actor, Event event);
	};

