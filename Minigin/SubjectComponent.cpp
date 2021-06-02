#include "MiniginPCH.h"
#include "SubjectComponent.h"

dae::SubjectComponent::SubjectComponent(GameObject* parent)
	:BaseComponent(parent)
{
	for (size_t i = 0; i < 3; ++i)
	{
		m_Observers[i] = nullptr;
	}
}

void dae::SubjectComponent::AddObserver(Observer* observer)
{
	for(size_t i = 0; i < 3; ++i)
	{
		if(m_Observers[i] != nullptr)
		{
			m_Observers[i] = observer;
		}
	}
}

void dae::SubjectComponent::RemoveObserver(Observer* observer)
{
	for (size_t i = 0; i < 3; ++i)
	{
		if(m_Observers[i] == observer)
		{
			m_Observers[i] = nullptr;
		}
	}
}

void dae::SubjectComponent::Notify(const GameObject& actor, Event event)
{
	for(size_t i = 0; i < 3; ++i)
	{
		m_Observers[i]->Notify(actor, event);
	}
}
