#pragma once

struct Vec2
{
	float x;
	float y;


public:
	bool IsZero() const
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}
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

	Vec2 operator - ()
	{
		return Vec2(-x, -y);
	}

	Vec2& operator= (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator +(Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	Vec2 operator -(Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}
	Vec2 operator *(Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator /(Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}
	Vec2 operator *(int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}
	Vec2 operator *(float _i)
	{
		return Vec2(x * _i, y * _i);
	}
	void operator +=(Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}
	Vec2 operator /(float _f)
	{
		assert(0.f != _f);
		return Vec2(x / _f, y / _f);
	}
	void operator *=(Vec2 _vOther)
	{
		x *= _vOther.x;
		y *= _vOther.y;
	}
	void operator *=(float _f)
	{
		x *= _f;
		y *= _f;
	}
	void operator -=(float _f)
	{
		x -= _f;
		y -= _f;
	}
	void operator -=(Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}
	bool operator ==(Vec2 _vOther)
	{
		if (x == _vOther.x && y == _vOther.y)
			return true;
		return false;
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