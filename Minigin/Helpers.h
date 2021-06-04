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

struct float2
{
	float2()
	{
		x = 0;
		y = 0;
	}
	float2(float X, float Y)
	{
		x = X;
		y = Y;
	}
	float x;
	float y;
};

struct Rect
{
	int x;
	int y;
	int w;
	int h;
};

enum class Event
{
	MoveTile,
	Died,
	LevelCleared
};

enum class GameType
{
	Single,
	Double,
	Return
};
