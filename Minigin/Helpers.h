#pragma once

struct int2
{
	int2()
	{
		x = 0;
		y = 0;
	}
	int2(int X, int Y)
	{
		x = X;
		y = Y;
	}
	int x;
	int y;
};

struct Rect
{
	int x;
	int y;
	int w;
	int h;
};
