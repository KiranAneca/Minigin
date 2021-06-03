#pragma once
#include "Minigin.h"

class Application : public Minigin
{
	void InitializeApplication() override;
	void LoadApllication() const override;
	void CleanupApplication() override;
	void RunApplication() override;

private:

	int m_AmountOfPlayers;
};

