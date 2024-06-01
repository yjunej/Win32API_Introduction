#pragma once

enum KEY_STATE
{
	TAP, // Press
	HOLD, // Press and Hold
	AWAY, // Press and Release
	NONE, // Not Triggered
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST,
};




struct tKeyInfo
{
	KEY_STATE	eState;
	bool		bPressed;
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;

public:
	int Init();
	void Update();

public:
	KEY_STATE GetKeyState(KEY _eKey) {return m_vecKey[(int)_eKey].eState;}
};

