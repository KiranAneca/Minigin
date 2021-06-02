#include "MiniginPCH.h"
#include "TimeComponent.h"

#include "GameObject.h"
#include "TextRenderComponent.h"

dae::TimeComponent::TimeComponent(GameObject* parent)
	:BaseComponent(parent)
	, m_Frames(0)
	, m_SecondCounter(0)
{
}

dae::TimeComponent::~TimeComponent()
{
}

void dae::TimeComponent::Update(float deltaTime)
{
	m_SecondCounter += deltaTime;
	m_Frames++;
	if(m_SecondCounter >= 1.f)
	{
		auto comp = m_Parent->GetComponent<TextRenderComponent>();
		if (comp != nullptr)
		{
			std::string text{ "FPS: " + std::to_string(GetFrames()) };
			comp->SetText(text);
		}
		
		m_Frames = 0;
		m_SecondCounter -= 1.f;
	}
}

void dae::TimeComponent::Render() const
{
}

int dae::TimeComponent::GetFrames() const
{
	return m_Frames;
}
