#pragma once

struct Vec2
{
public:
	float x;
	float y;


public:
	float Distance(Vec2 _Other)
	{
		return sqrtf(powf(x - _Other.x, 2) + powf(y - _Other.y, 2));
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float f = Length();
		x /= f;
		y /= f;

		assert(f);

		return *this;
	}

	Vec2 operator + (Vec2 _Other) const
	{
		return Vec2(x + _Other.x, y + _Other.y);
	}

	void operator += (Vec2 _Other)
	{
		x += _Other.x;
		y += _Other.y;
	}

	Vec2 operator + (float _f) const
	{
		return Vec2(x + _f, y + _f);
	}

	Vec2 operator += (float _f)
	{
		x += _f;
		y += _f;
	}


	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}


	Vec2 operator - (Vec2 _Other) const
	{
		return Vec2(x - _Other.x, y - _Other.y);
	}

	Vec2 operator - (float _f) const
	{
		return Vec2(x - _f, y - _f);
	}

	void operator -=(float _f)  
	{
		x -= _f;
		y -= _f;
	}

	void operator -=(Vec2 _v)
	{
		x -= _v.x;
		y -= _v.y;
	}



	Vec2 operator * (Vec2 _Other) const
	{
		return Vec2(x * _Other.x, y * _Other.y);
	}

	Vec2 operator * (float _f) const
	{
		return Vec2(x * _f, y * _f);
	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}

	Vec2 operator / (Vec2 _Other) const
	{
		assert(_Other.x);
		assert(_Other.y);

		return Vec2(x / _Other.x, y / _Other.y);		
	}

	Vec2 operator / (float _f) const
	{
		assert(_f);
		return Vec2(x / _f, y / _f);
	}

	void operator /= (float _f)
	{
		assert(_f);

		x /= _f;
		y /= _f;
	}


	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x), y((float)_y)
	{}

	Vec2(UINT _x, UINT _y)
		: x((float)_x), y((float)_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}
};

struct FKeyData
{
	KEY			eKey;
	KEY_STATE	eState;
	bool		bPressed;
};


struct FMonInfo
{
	wchar_t szName[50];
	float HP;
	float MP;
	float Att;
	float Int;
	float Speed;
};

struct FTask
{
	TASK_TYPE Type;
	UINT_PTR  Param_1;
	UINT_PTR  Param_2;
};



struct FSelectPen
{
private:
	HPEN hPrevPen;
	HDC  hCurDC;

public:
	FSelectPen(HDC _dc, PEN_TYPE _Type);
	~FSelectPen();
};


struct FSelectBrush
{
private:
	HBRUSH	hPrevBrush;
	HDC		hCurDC;

public:
	FSelectBrush(HDC _dc, HBRUSH _brush);
	~FSelectBrush();
};

struct FLog
{
	LOG_LEVEL Level;
	wstring	  Message;
	float	  AccTime;
};

