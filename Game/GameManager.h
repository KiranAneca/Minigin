#pragma once
#include "Singleton.h"
#include "Helpers.h"
#include <iostream>

class GameManager final : public Singleton<GameManager>
{
public:
	void AddTilesLeft(int amount);
	void SetLives(int amount);
	void LoseLife();

	int GetLives() const;
	int GetTilesLeft() const;

	int GetLevel() const;
	void SetLevel(int lvl);

	int GetScore() const;
	void AddScore(int amount);
	
	void SetGameType(GameType type);
	GameType GetGameType() const;
	std::string GetTileBaseTexture() const;
	std::string GetTileIntermediateTexture() const;
	std::string GetTileJumpedTexture() const;

	bool CanSeeMenu() const;
	void SetSeeMenu(bool active);
private:
	friend class Singleton<GameManager>;
	GameManager() = default;

	int m_TilesLeft;
	int m_Lives;
	int m_Score;

	int m_Level = 1;
	bool m_ShowMenu = true;

	std::string m_TileBaseTexture = "CubeBase.png";
	std::string m_TileIntermediateTexture = "CubeIntermediate.png";
	std::string m_TileCompletedTexture = "CubeJumped.png";
	GameType m_GameType = GameType::Single;
};

