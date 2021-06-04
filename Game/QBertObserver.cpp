#include "QBertObserver.h"
#include "GridComponent.h"
#include "RenderComponent.h"
#include "GameManager.h"
#include "Helpers.h"
#include <windows.h>

#include <iostream>

QBertObserver::QBertObserver(GameObject* parent)
	:Observer(parent)
{
}

void QBertObserver::Notify(const GameObject& actor, Event event)
{
	int2 pos = m_Parent->GetComponent<GridComponent>()->GetGrid();
	int2 otherPos = actor.GetComponent<GridComponent>()->GetGrid();

	auto& gm = GameManager::GetInstance();
	auto rc = m_Parent->GetComponent<RenderComponent>();

	std::string baseTexture = gm.GetTileBaseTexture();
	std::string intermediateTexture = gm.GetTileIntermediateTexture();
	std::string jumpedTexture = gm.GetTileJumpedTexture();
	
	switch (event)
	{
	case Event::MoveTile:
		if (pos.x == otherPos.x && pos.y == otherPos.y)
		{
			switch (gm.GetGameType())
			{
			case GameType::Single:
				if (rc->GetTexture() == baseTexture)
				{
					rc->SetTexture(jumpedTexture);
					gm.AddTilesLeft(-1);
				}
				break;
			case GameType::Double:
				if (rc->GetTexture() == baseTexture)
				{
					rc->SetTexture(intermediateTexture);
				}
				else if(rc->GetTexture() == intermediateTexture)
				{
					rc->SetTexture(jumpedTexture);
					gm.AddTilesLeft(-1);
				}
				break;
			case GameType::Return:
				if (rc->GetTexture() == baseTexture)
				{
					rc->SetTexture(jumpedTexture);
					gm.AddTilesLeft(-1);
				}
				else if(rc->GetTexture() == jumpedTexture)
				{
					rc->SetTexture(baseTexture);
					gm.AddTilesLeft(1);
				}
				break;
			}
		}
		break;
	case Event::Died:
		break;
	case Event::LevelCleared:
		rc->SetTexture(baseTexture);
		gm.AddTilesLeft(1);
		break;
	}
}

void QBertObserver::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void QBertObserver::Render() const
{
}
