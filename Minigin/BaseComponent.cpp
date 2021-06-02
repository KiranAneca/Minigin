#include "MiniginPCH.h"
#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(GameObject* parent)
	: m_Parent(parent)
{
}

dae::BaseComponent::~BaseComponent()
{
}

void dae::BaseComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, m_Transform.GetPosition().z);
}
