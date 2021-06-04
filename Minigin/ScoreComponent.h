#pragma once
#include "BaseComponent.h"


class ScoreComponent : public BaseComponent
{
public:
	ScoreComponent(GameObject* parent);
	~ScoreComponent();

	void Update(float deltaTime) override;
	void Render() const override;

	void SetScoreType(std::string text);
	std::string GetScoreType() const;
	void SetScore(int amount);
	void AddScore(int amount);
	int GetScore() const;

private:
	int m_Score;
	std::string m_ScoreType;
};

