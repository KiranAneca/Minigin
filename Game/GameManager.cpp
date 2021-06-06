#include "GameManager.h"
#include "json.hpp"
#include <fstream>
#include "SceneManager.h"

void GameManager::AddTilesLeft(int amount)
{
	m_TilesLeft += amount;
}

void GameManager::SetLives(int amount)
{
	m_Lives = amount;
}

void GameManager::LoseLife()
{
	m_Lives--;
}

int GameManager::GetLives() const
{
	return m_Lives;
}

int GameManager::GetTilesLeft() const
{
	return m_TilesLeft;
}

int GameManager::GetLevel() const
{
	return m_Level;
}

void GameManager::SetLevel(int lvl)
{
	m_Level = lvl;
	if(lvl > (int) m_Levels.size())
	{
		auto& sceneManager = SceneManager::GetInstance();
		GameManager::GetInstance().SetSeeMenu(true);
		sceneManager.SetSceneActive(true, "MainMenu");
		sceneManager.DeleteScene("GameSceneSingle");
		sceneManager.DeleteScene("GameSceneMulti");
		sceneManager.DeleteScene("GameSceneVersus");
	}
	else
	{
		if (m_Levels[m_Level - 1].Type == "Single")
		{
			m_GameType = GameType::Single;
		}
		else if (m_Levels[m_Level - 1].Type == "Double")
		{
			m_GameType = GameType::Double;
		}
		else if (m_Levels[m_Level - 1].Type == "Return")
		{
			m_GameType = GameType::Return;
		}
	}
}

int GameManager::GetScore() const
{
	return m_Score;
}

void GameManager::AddScore(int amount)
{
	m_Score += amount;
}

void GameManager::SetGameType(GameType type)
{
	m_GameType = type;
}

GameType GameManager::GetGameType() const
{
	return m_GameType;
}

std::string GameManager::GetTileBaseTexture() const
{
	return m_TileBaseTexture;
}

std::string GameManager::GetTileIntermediateTexture() const
{
	return m_TileIntermediateTexture;
}

std::string GameManager::GetTileJumpedTexture() const
{
	return m_TileCompletedTexture;
}

bool GameManager::CanSeeMenu() const
{
	return m_ShowMenu;
}

void GameManager::SetSeeMenu(bool active)
{
	m_ShowMenu = active;
	if(active)
	{
		m_Score = 0;
	}
}

GameManager::GameManager()
{
	std::fstream file("Data/Levels.json");
	nlohmann::json temp;
	if(file.is_open())
	{
		file >> temp;
		for (auto obj : temp["Levels"])
		{
			levelLayout level;
			level.Level = obj["Level"];
			level.Type = obj["Type"];
			m_Levels.push_back(level);
		}
	}
}
