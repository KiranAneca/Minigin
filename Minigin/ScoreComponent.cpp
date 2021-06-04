#include "MiniginPCH.h"
#include "ScoreComponent.h"

#include "GameObject.h"
#include "TextRenderComponent.h"

ScoreComponent::ScoreComponent(GameObject* parent)
	: BaseComponent(parent)
    , m_Score(0)
{
}

ScoreComponent::~ScoreComponent()
{
}

void ScoreComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void ScoreComponent::Render() const
{
}

void ScoreComponent::SetScoreType(std::string text)
{
	m_ScoreType = text;
	
	auto comp = m_Parent->GetComponent<TextRenderComponent>();
	if (comp != nullptr)
	{
		std::string temp{ m_ScoreType + ": " + std::to_string(m_Score) };
		comp->SetText(temp);
	}
}

std::string ScoreComponent::GetScoreType() const
{
	return m_ScoreType;
}

void ScoreComponent::SetScore(int amount)
{
	m_Score = amount;

	auto comp = m_Parent->GetComponent<TextRenderComponent>();
	if (comp != nullptr)
	{
		std::string text{ m_ScoreType + ": " + std::to_string(m_Score) };
		comp->SetText(text);
	}
}

void ScoreComponent::AddScore(int amount)
{
	m_Score += amount;

	auto comp = m_Parent->GetComponent<TextRenderComponent>();
	if (comp != nullptr)
	{
		std::string text{ m_ScoreType + ": " + std::to_string(m_Score) };
		comp->SetText(text);
	}
}

int ScoreComponent::GetScore() const
{
	return m_Score;
}
