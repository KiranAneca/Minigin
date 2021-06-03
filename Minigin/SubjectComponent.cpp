#include "MiniginPCH.h"
#include "SubjectComponent.h"

SubjectComponent::SubjectComponent(GameObject* parent)
	:BaseComponent(parent)
{

}

void SubjectComponent::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void SubjectComponent::RemoveObserver(Observer* observer)
{
	for (size_t i = 0; i < m_Observers.size(); ++i)
	{
		if(m_Observers[i] == observer)
		{
			m_Observers[i] = nullptr;
		}
	}
}

void SubjectComponent::Notify(const GameObject& actor, Event event)
{
	for(size_t i = 0; i < m_Observers.size(); ++i)
	{
		if(m_Observers[i] != nullptr)
		{
			m_Observers[i]->Notify(actor, event);
		}
	}
}

void SubjectComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void SubjectComponent::Render() const
{
}
