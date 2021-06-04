#include <iostream>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include <Minigin.h>
#include "Application.h"

int main()
{
	Application game;
	game.Run();
	return 0;
}

