#pragma once

class CObject;

class CGravity
{
private:
	CObject* m_pOwner;
	bool m_bGround;

public:
	void PostUpdate();
	void SetGround(bool _b);

public:
	CGravity();
	~CGravity();
	friend class CObject;
};

