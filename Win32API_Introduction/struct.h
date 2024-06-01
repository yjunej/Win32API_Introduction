#pragma once

struct Vec2
{
	float x;
	float y;


public:
	float GetLength()
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float length = GetLength();
		assert(length != 0.f);
		this->x /= length;
		this->y /= length;
		return *this;
	}

	Vec2& operator= (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}


public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

};