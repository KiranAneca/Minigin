#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "Events.h"

	class SubjectComponent : public BaseComponent
	{
	public:
		SubjectComponent(GameObject* parent);
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(const GameObject& actor, Event event);
	
	private:
		Observer* m_Observers[3];
	};

