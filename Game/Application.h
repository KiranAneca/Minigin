#pragma once
#include "Minigin.h"

class Application : public Minigin
{
public:
	void InitializeApplication() override;
	void LoadApllication() const override;
	void CleanupApplication() override;
	void RunApplication() override;
	
	void LoadMainMenu() const;
	void LoadGameSinglePlayer() const;
	void LoadGameMultiplayer() const;
	void LoadGameVersus() const;

private:
	
	int m_AmountOfPlayers;

};

