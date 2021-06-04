#include "MiniginPCH.h"
#include "Observer.h"
#include "GridComponent.h"
#include "ScoreComponent.h"
#include "RenderComponent.h"


Observer::Observer(GameObject* parent)
	:BaseComponent(parent)
{
}

void Observer::Notify(const GameObject& actor, Event event)
{
	UNREFERENCED_PARAMETER(actor);
	UNREFERENCED_PARAMETER(event);
}

void Observer::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void Observer::Render() const
{
}
