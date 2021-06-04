#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "Helpers.h"

	class SubjectComponent : public BaseComponent
	{
	public:
		SubjectComponent(GameObject* parent);
		
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(const GameObject& actor, Event event);

		void Update(float deltaTime) override;
		void Render() const override;
	
	private:
		std::vector<Observer*> m_Observers;
	};

