#pragma once
#include "Minigin.h"

class Application : public Minigin
{
	void InitializeApplication() override;
	void LoadApllication() const override;
	void CleanupApplication() override;
	void RunApplication() override;

private:
	void LoadMainMenu() const;
	void LoadGameSinglePlayer() const;
	void LoadGameMultiplayer() const;
	void LoadGameVersus() const;
	
	int m_AmountOfPlayers;

};

