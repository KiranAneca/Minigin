#include "MiniginPCH.h"
#include "BaseComponent.h"

BaseComponent::BaseComponent(GameObject* parent)
	: m_Parent(parent)
{
}

BaseComponent::~BaseComponent()
{
}

void BaseComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, m_Transform.GetPosition().z);
}

float2 BaseComponent::GetPosition() const
{
	float2 temp;
	temp.x = m_Transform.GetPosition().x;
	temp.y = m_Transform.GetPosition().y;
	return temp;
}
