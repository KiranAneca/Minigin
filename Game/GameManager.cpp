#include "GameManager.h"

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
}
