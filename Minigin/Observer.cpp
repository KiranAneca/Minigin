#include "MiniginPCH.h"
#include "Observer.h"

Observer::Observer()
{
}

void Observer::Notify(const GameObject& actor, Event event)
{
	UNREFERENCED_PARAMETER(actor);
	switch(event)
	{
	case Event::ColorTile:
		break;
	case Event::Died:
		break;
	}
}
